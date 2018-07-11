/***********************************************************************************************************************
 * Copyright [2017] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_motor.c
 * Description  : Common Motor control functions and global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_motor_api_changed.h"
#include "r_gpt.h"
#include "bsp_api.h"
#include "common_data.h"









volatile uint32_t pwm_cycle_cntr = 0;
void (*sf_callback)(void) = NULL;
bool irq_handler_set = false;
int32_t     g_motor_count = 0;
motor_instance_t const *g_motors[16];
int16_t     g_pwm_timer_count;

uint8_t pattern_index = 1;

extern mtr_added_ctrl_t *p_mtr_pattern_ctrl;
extern trap_phase_state_t trap_pattern[6];
extern phase_pin_ctrl_t *p_pins_ctrl;
extern phase_pin_ctrl_t pins_ctrl[6];


ioport_level_t level = IOPORT_LEVEL_LOW;


/* Interrupt handler for high speed motor control loops */
void pwm_counter_overflow (void);
/*interrupt handler to switch commutation after detecting bemf */
void timer_change_commut_isr(void);
volatile pin_duty_state pins_u;
volatile pin_duty_state pins_v;
volatile pin_duty_state pins_w;

volatile bool switch_ol_to_cl = 0;



void pwm_counter_overflow (void)
{

    //this interrupt is running at 20KHz

    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_SSP_VectorInfoGet(irq, &p_vector_info);
    motor_instance_t *trap_motor = g_motors[0]; //hardcode the motor that has a trapezoidal commutation scheme


    if (sf_callback != NULL)
    {
        /* If there is a motor owner - call its callback */
        sf_callback();
    }
    else
    {
        /* If the motor modules are stand alone - call their control function */
        for (int32_t i = 0; i < g_motor_count; i++)
        {
            if (g_motors[i]->p_api != NULL)
                g_motors[i]->p_api->control(g_motors[i]->p_ctrl);
        }
    }
    /* Keep track of the number of PWM interrupts (control cycles) */
    pwm_cycle_cntr++;

    if(pwm_cycle_cntr >= p_mtr_pattern_ctrl->vel_accel.velocity)
    {
        pwm_cycle_cntr = 0;

        //update pointer holding data about pin levels for specific trapezoidal commutation
        p_pins_ctrl++;
        if(p_pins_ctrl > &pins_ctrl[5])
        {
            p_pins_ctrl = &pins_ctrl[0]; //reset pointer to beginning of pattern array
        }


        //get values from memory so block timers can be updated faster (promote synchronicity of timer updates)
        pins_u = p_pins_ctrl->u_phase_pins.pins_duty_reg;
        pins_v = p_pins_ctrl->v_phase_pins.pins_duty_reg;
        pins_w = p_pins_ctrl->w_phase_pins.pins_duty_reg;

        /*** Update timer pins output ***/
        //update U timer
        trap_motor->p_ctrl->p_gpt_u->GTUDDTYC = pins_u;   //changing the OADTY/OBDTY bits allows for synchronous changing of the timer's pin outputs at a timer underflow

        //update V timer
        trap_motor->p_ctrl->p_gpt_v->GTUDDTYC = pins_v;

        //update W timer
        trap_motor->p_ctrl->p_gpt_w->GTUDDTYC = pins_w;

        R_S12ADC0->ADANSA0 = 0;
        if(pins_u == 0x02020001)
        {
            R_S12ADC0->ADCMPCR_b.CMPAE = 0;
            R_S12ADC0->ADANSA0 = 0x0001;
            R_S12ADC0->ADCMPCR_b.CMPAE = 1;
        }

        else if(pins_v == 0x02020001)
        {
            R_S12ADC0->ADCMPCR_b.CMPAE = 0;
            R_S12ADC0->ADANSA0 = 0x0002;
            R_S12ADC0->ADCMPCR_b.CMPAE = 1;
        }

        else if(pins_w == 0x02020001)
        {
            R_S12ADC0->ADCMPCR_b.CMPAE = 0;
            R_S12ADC0->ADANSA0 = 0x0004;
            R_S12ADC0->ADCMPCR_b.CMPAE = 1;
        }
    }
    else if (p_mtr_pattern_ctrl->ctrl_type == CLOSED_LOOP_CONTROL)
    {
//        switch_ol_to_cl = 1;
//
//        //enable the adc interrupt to detect zero cross
//        //enable adc interrupt
//        ssp_feature_t ssp_feature = {{ (ssp_ip_t) 0 } };
//        ssp_feature.channel = 0;
//        ssp_feature.unit = 0U;
//        ssp_feature.id = SSP_IP_ADC;
//
//        fmi_event_info_t event_info =
//        { (IRQn_Type) 0U };
//        g_fmi_on_fmi.eventInfoGet (&ssp_feature, SSP_SIGNAL_ADC_WINDOW_A, &event_info);
//        NVIC_SetPriority (event_info.irq, 2);
//
//        R_BSP_IrqStatusClear (event_info.irq);
//        NVIC_ClearPendingIRQ (event_info.irq);
//        NVIC_EnableIRQ (event_info.irq);
//
//
//        //enable gpt32 delay interrupt
//        ssp_feature.channel = 4;
//        ssp_feature.unit = 0U;
//        ssp_feature.id = SSP_IP_GPT;
//
//        g_fmi_on_fmi.eventInfoGet (&ssp_feature, SSP_SIGNAL_GPT_COUNTER_OVERFLOW, &event_info);
//        NVIC_SetPriority (event_info.irq, 1);
//
//        R_BSP_IrqStatusClear (event_info.irq);
//        NVIC_ClearPendingIRQ (event_info.irq);
//        NVIC_EnableIRQ (event_info.irq);
    }

    /** Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
    if (g_motors[0]->p_ctrl != NULL)
        g_pwm_timer_count = (int16_t)g_motors[0]->p_ctrl->p_gpt_u->GTCNT;
} /* End of function gpt_counter_overflow_common */


void adc_comp_isr();
void adc_comp_isr()
{
    SF_CONTEXT_SAVE
    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_SSP_VectorInfoGet(irq, &p_vector_info);
//
//    if(switch_ol_to_cl == 1)
//    {
//        switch_ol_to_cl = 0;
//        //disable gpt interrupt
//        ssp_feature_t ssp_feature = {{ (ssp_ip_t) 0 } };
//        ssp_feature.channel = 0;
//        ssp_feature.unit = 0U;
//        ssp_feature.id = SSP_IP_GPT;
//        fmi_event_info_t event_info = { (IRQn_Type) 0U };
//        g_fmi_on_fmi.eventInfoGet (&ssp_feature, SSP_SIGNAL_GPT_COUNTER_OVERFLOW, &event_info);
//        NVIC_SetPriority (event_info.irq, 1);
//
//        R_BSP_IrqStatusClear (event_info.irq);
//        NVIC_ClearPendingIRQ (event_info.irq);
//        NVIC_DisableIRQ (event_info.irq);
//
////    }
//    //enable timer for commutation delay after zero cross detection
//    R_GPTA4->GTCR_b.CST = 1;
//
//    if(level == IOPORT_LEVEL_LOW)
//    {
//        level = IOPORT_LEVEL_HIGH;
//    }
//    else
//    {
//        level = IOPORT_LEVEL_LOW;
//    }
//    g_ioport.p_api->pinWrite(IOPORT_PORT_05_PIN_00, level); //toggle pin at interrupt for change commutation

    //update ADC variable for logging, do this every interrupt
    if(pins_u == 0x02020001)
    {
        g_motors[0]->p_ctrl->adc1_raw = (int16_t)R_S12ADC0->ADDRn[0];
    }
    else if(pins_v == 0x02020001)
    {
        g_motors[0]->p_ctrl->adc1_raw = (int16_t)R_S12ADC0->ADDRn[1];
    }
    else if(pins_w == 0x02020001)
    {
        g_motors[0]->p_ctrl->adc1_raw = (int16_t)R_S12ADC0->ADDRn[2];
    }
    /** Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
    SF_CONTEXT_RESTORE
}


void timer_change_commut_isr()
{
    SF_CONTEXT_SAVE
    ssp_vector_info_t * p_vector_info = NULL;
    IRQn_Type irq = R_SSP_CurrentIrqGet();
    R_SSP_VectorInfoGet(irq, &p_vector_info);


    motor_instance_t *trap_motor = g_motors[0]; //hardcode the motor that has a trapezoidal commutation scheme

    //update pointer holding data about pin levels for specific trapezoidal commutation
    p_pins_ctrl++;
    if(p_pins_ctrl > &pins_ctrl[5])
    {
        p_pins_ctrl = &pins_ctrl[0]; //reset pointer to beginning of pattern array
    }


    //get values from memory so block timers can be updated faster (promote synchronicity of timer updates)
    pins_u = p_pins_ctrl->u_phase_pins.pins_duty_reg;
    pins_v = p_pins_ctrl->v_phase_pins.pins_duty_reg;
    pins_w = p_pins_ctrl->w_phase_pins.pins_duty_reg;

    /*** Update timer pins output ***/
    //update U timer
    trap_motor->p_ctrl->p_gpt_u->GTUDDTYC = pins_u;   //changing the OADTY/OBDTY bits allows for synchronous changing of the timer's pin outputs at a timer underflow

    //update V timer
    trap_motor->p_ctrl->p_gpt_v->GTUDDTYC = pins_v;

    //update W timer
    trap_motor->p_ctrl->p_gpt_w->GTUDDTYC = pins_w;

    R_S12ADC0->ADANSA0 = 0;
    if(pins_u == 0x02020001)
    {
        R_S12ADC0->ADCMPCR_b.CMPAE = 0;
        R_S12ADC0->ADANSA0 = 0x0001;
        R_S12ADC0->ADCMPCR_b.CMPAE = 1;
    }

    else if(pins_v == 0x02020001)
    {
        R_S12ADC0->ADCMPCR_b.CMPAE = 0;
        R_S12ADC0->ADANSA0 = 0x0002;
        R_S12ADC0->ADCMPCR_b.CMPAE = 1;
    }

    else if(pins_w == 0x02020001)
    {
        R_S12ADC0->ADCMPCR_b.CMPAE = 0;
        R_S12ADC0->ADANSA0 = 0x0004;
        R_S12ADC0->ADCMPCR_b.CMPAE = 1;
    }

    R_BSP_IrqStatusClear(irq);
    SF_CONTEXT_RESTORE
}






