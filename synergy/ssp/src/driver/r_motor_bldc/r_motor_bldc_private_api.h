/***********************************************************************************************************************
 * Copyright [2015] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
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

#ifndef R_Motor_BLDC_PRIVATE_API_H
#define R_Motor_BLDC_PRIVATE_API_H

/***********************************************************************************************************************
 * Private Instance API Functions. DO NOT USE! Use functions through Interface API structure instead.
 **********************************************************************************************************************/
ssp_err_t R_Motor_BLDC_Open (motor_ctrl_t * const p_ctrl, motor_cfg_t * const p_cfg);
ssp_err_t R_Motor_BLDC_Setup (motor_ctrl_t * const p_ctrl, int32_t ecpr);
ssp_err_t R_Motor_BLDC_Control (motor_ctrl_t * const p_ctrl);
ssp_err_t R_Motor_BLDC_Reset (motor_ctrl_t * const p_ctrl);
ssp_err_t R_Motor_BLDC_InfoGet (motor_ctrl_t * const p_ctrl, motor_info_t * const p_info);
ssp_err_t R_Motor_BLDC_CounterGet (motor_ctrl_t * const p_ctrl, int32_t * const p_value);
ssp_err_t R_Motor_BLDC_Close (motor_ctrl_t * const p_ctrl);
ssp_err_t R_Motor_BLDC_VersionGet (ssp_version_t * const p_version);

#endif /* R_Motor_BLDC_PRIVATE_API_H */