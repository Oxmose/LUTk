/*******************************************************************************
 * @file boot.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 23/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel's main entry point for the Cortex M4 CPU.
 *
 * @details Kernel entry point and cpu initialization.
 ******************************************************************************/
.syntax unified

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

.equ MAIN_STACK_ADDRESS, 0x20001000

/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/
.extern _start_bss
.extern _end_bss
.extern _start_init_data
.extern _start_data
.extern _end_data

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/
.extern kernel_kickstart
.extern kernel_panic
.extern __bsp_init
.extern __fpu_init
.extern __nvic_init

.extern __extint_0
.extern __extint_1
.extern __extint_2
.extern __extint_3
.extern __extint_4
.extern __extint_5
.extern __extint_6
.extern __extint_7
.extern __extint_8
.extern __extint_9
.extern __extint_10
.extern __extint_11
.extern __extint_12
.extern __extint_13
.extern __extint_14
.extern __extint_15
.extern __extint_16
.extern __extint_17
.extern __extint_18
.extern __extint_19
.extern __extint_20
.extern __extint_21
.extern __extint_22
.extern __extint_23
.extern __extint_24
.extern __extint_25
.extern __extint_26
.extern __extint_27
.extern __extint_28
.extern __extint_29
.extern __extint_30
.extern __extint_31
.extern __extint_32
.extern __extint_33
.extern __extint_34
.extern __extint_35
.extern __extint_36
.extern __extint_37
.extern __extint_38
.extern __extint_39
.extern __extint_40
.extern __extint_41
.extern __extint_42
.extern __extint_43
.extern __extint_44
.extern __extint_45
.extern __extint_46
.extern __extint_47
.extern __extint_48
.extern __extint_49
.extern __extint_50
.extern __extint_51
.extern __extint_52
.extern __extint_53
.extern __extint_54
.extern __extint_55
.extern __extint_56
.extern __extint_57
.extern __extint_58
.extern __extint_59
.extern __extint_60
.extern __extint_61
.extern __extint_62
.extern __extint_63
.extern __extint_64
.extern __extint_65
.extern __extint_66
.extern __extint_67
.extern __extint_68
.extern __extint_69
.extern __extint_70
.extern __extint_71
.extern __extint_72
.extern __extint_73
.extern __extint_74
.extern __extint_75
.extern __extint_76
.extern __extint_77
.extern __extint_78
.extern __extint_79
.extern __extint_80
.extern __extint_81
.extern __extint_82
.extern __extint_83
.extern __extint_84
.extern __extint_85
.extern __extint_86
.extern __extint_87
.extern __extint_88
.extern __extint_89
.extern __extint_90
.extern __extint_91
.extern __extint_92
.extern __extint_93
.extern __extint_94
.extern __extint_95
.extern __extint_96
.extern __extint_97
.extern __extint_98
.extern __extint_99
.extern __extint_100
.extern __extint_101
.extern __extint_102
.extern __extint_103
.extern __extint_104
.extern __extint_105
.extern __extint_106
.extern __extint_107
.extern __extint_108
.extern __extint_109
.extern __extint_110
.extern __extint_111
.extern __extint_112
.extern __extint_113
.extern __extint_114
.extern __extint_115
.extern __extint_116
.extern __extint_117
.extern __extint_118
.extern __extint_119
.extern __extint_120
.extern __extint_121
.extern __extint_122
.extern __extint_123
.extern __extint_124
.extern __extint_125
.extern __extint_126
.extern __extint_127
.extern __extint_128
.extern __extint_129
.extern __extint_130
.extern __extint_131
.extern __extint_132
.extern __extint_133
.extern __extint_134
.extern __extint_135
.extern __extint_136
.extern __extint_137
.extern __extint_138
.extern __extint_139
.extern __extint_140
.extern __extint_141
.extern __extint_142
.extern __extint_143
.extern __extint_144
.extern __extint_145
.extern __extint_146
.extern __extint_147
.extern __extint_148
.extern __extint_149
.extern __extint_150
.extern __extint_151
.extern __extint_152
.extern __extint_153
.extern __extint_154
.extern __extint_155
.extern __extint_156
.extern __extint_157
.extern __extint_158
.extern __extint_159
.extern __extint_160
.extern __extint_161
.extern __extint_162
.extern __extint_163
.extern __extint_164
.extern __extint_165
.extern __extint_166
.extern __extint_167
.extern __extint_168
.extern __extint_169
.extern __extint_170
.extern __extint_171
.extern __extint_172
.extern __extint_173
.extern __extint_174
.extern __extint_175
.extern __extint_176
.extern __extint_177
.extern __extint_178
.extern __extint_179
.extern __extint_180
.extern __extint_181
.extern __extint_182
.extern __extint_183
.extern __extint_184
.extern __extint_185
.extern __extint_186
.extern __extint_187
.extern __extint_188
.extern __extint_189
.extern __extint_190
.extern __extint_191
.extern __extint_192
.extern __extint_193
.extern __extint_194
.extern __extint_195
.extern __extint_196
.extern __extint_197
.extern __extint_198
.extern __extint_199
.extern __extint_200
.extern __extint_201
.extern __extint_202
.extern __extint_203
.extern __extint_204
.extern __extint_205
.extern __extint_206
.extern __extint_207
.extern __extint_208
.extern __extint_209
.extern __extint_210
.extern __extint_211
.extern __extint_212
.extern __extint_213
.extern __extint_214
.extern __extint_215
.extern __extint_216
.extern __extint_217
.extern __extint_218
.extern __extint_219
.extern __extint_220
.extern __extint_221
.extern __extint_222
.extern __extint_223
.extern __extint_224
.extern __extint_225
.extern __extint_226
.extern __extint_227
.extern __extint_228
.extern __extint_229
.extern __extint_230
.extern __extint_231
.extern __extint_232
.extern __extint_233
.extern __extint_234
.extern __extint_235
.extern __extint_236
.extern __extint_237
.extern __extint_238
.extern __extint_239
.extern __extint_240
.extern __extint_241
.extern __extint_242
.extern __extint_243
.extern __extint_244
.extern __extint_245
.extern __extint_246
.extern __extint_247
.extern __extint_248
.extern __extint_249
.extern __extint_250
.extern __extint_251
.extern __extint_252
.extern __extint_253
.extern __extint_254
.extern __extint_255

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/
.global __rst_handler
.global __kernel_init

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .int_vect,"a",%progbits

__rst_vector:
    .word MAIN_STACK_ADDRESS     /* Reset MSP */
    .word __rst_handler          /* Reset PC */
    .word __exc_nmi_handler      
    .word __exc_hardfault_handler
    .word __exc_mpu_handler    
    .word __exc_bus_handler
    .word __exc_usage_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_undef_handler
    .word __exc_svc_handler
    .word __exc_debug_handler
    .word __exc_undef_handler
    .word __exc_pensv_handler
    .word __sys_tick_handler

    .word __extint_0
    .word __extint_1
    .word __extint_2
    .word __extint_3
    .word __extint_4
    .word __extint_5
    .word __extint_6
    .word __extint_7
    .word __extint_8
    .word __extint_9
    .word __extint_10
    .word __extint_11
    .word __extint_12
    .word __extint_13
    .word __extint_14
    .word __extint_15
    .word __extint_16
    .word __extint_17
    .word __extint_18
    .word __extint_19
    .word __extint_20
    .word __extint_21
    .word __extint_22
    .word __extint_23
    .word __extint_24
    .word __extint_25
    .word __extint_26
    .word __extint_27
    .word __extint_28
    .word __extint_29
    .word __extint_30
    .word __extint_31
    .word __extint_32
    .word __extint_33
    .word __extint_34
    .word __extint_35
    .word __extint_36
    .word __extint_37
    .word __extint_38
    .word __extint_39
    .word __extint_40
    .word __extint_41
    .word __extint_42
    .word __extint_43
    .word __extint_44
    .word __extint_45
    .word __extint_46
    .word __extint_47
    .word __extint_48
    .word __extint_49
    .word __extint_50
    .word __extint_51
    .word __extint_52
    .word __extint_53
    .word __extint_54
    .word __extint_55
    .word __extint_56
    .word __extint_57
    .word __extint_58
    .word __extint_59
    .word __extint_60
    .word __extint_61
    .word __extint_62
    .word __extint_63
    .word __extint_64
    .word __extint_65
    .word __extint_66
    .word __extint_67
    .word __extint_68
    .word __extint_69
    .word __extint_70
    .word __extint_71
    .word __extint_72
    .word __extint_73
    .word __extint_74
    .word __extint_75
    .word __extint_76
    .word __extint_77
    .word __extint_78
    .word __extint_79
    .word __extint_80
    .word __extint_81
    .word __extint_82
    .word __extint_83
    .word __extint_84
    .word __extint_85
    .word __extint_86
    .word __extint_87
    .word __extint_88
    .word __extint_89
    .word __extint_90
    .word __extint_91
    .word __extint_92
    .word __extint_93
    .word __extint_94
    .word __extint_95
    .word __extint_96
    .word __extint_97
    .word __extint_98
    .word __extint_99
    .word __extint_100
    .word __extint_101
    .word __extint_102
    .word __extint_103
    .word __extint_104
    .word __extint_105
    .word __extint_106
    .word __extint_107
    .word __extint_108
    .word __extint_109
    .word __extint_110
    .word __extint_111
    .word __extint_112
    .word __extint_113
    .word __extint_114
    .word __extint_115
    .word __extint_116
    .word __extint_117
    .word __extint_118
    .word __extint_119
    .word __extint_120
    .word __extint_121
    .word __extint_122
    .word __extint_123
    .word __extint_124
    .word __extint_125
    .word __extint_126
    .word __extint_127
    .word __extint_128
    .word __extint_129
    .word __extint_130
    .word __extint_131
    .word __extint_132
    .word __extint_133
    .word __extint_134
    .word __extint_135
    .word __extint_136
    .word __extint_137
    .word __extint_138
    .word __extint_139
    .word __extint_140
    .word __extint_141
    .word __extint_142
    .word __extint_143
    .word __extint_144
    .word __extint_145
    .word __extint_146
    .word __extint_147
    .word __extint_148
    .word __extint_149
    .word __extint_150
    .word __extint_151
    .word __extint_152
    .word __extint_153
    .word __extint_154
    .word __extint_155
    .word __extint_156
    .word __extint_157
    .word __extint_158
    .word __extint_159
    .word __extint_160
    .word __extint_161
    .word __extint_162
    .word __extint_163
    .word __extint_164
    .word __extint_165
    .word __extint_166
    .word __extint_167
    .word __extint_168
    .word __extint_169
    .word __extint_170
    .word __extint_171
    .word __extint_172
    .word __extint_173
    .word __extint_174
    .word __extint_175
    .word __extint_176
    .word __extint_177
    .word __extint_178
    .word __extint_179
    .word __extint_180
    .word __extint_181
    .word __extint_182
    .word __extint_183
    .word __extint_184
    .word __extint_185
    .word __extint_186
    .word __extint_187
    .word __extint_188
    .word __extint_189
    .word __extint_190
    .word __extint_191
    .word __extint_192
    .word __extint_193
    .word __extint_194
    .word __extint_195
    .word __extint_196
    .word __extint_197
    .word __extint_198
    .word __extint_199
    .word __extint_200
    .word __extint_201
    .word __extint_202
    .word __extint_203
    .word __extint_204
    .word __extint_205
    .word __extint_206
    .word __extint_207
    .word __extint_208
    .word __extint_209
    .word __extint_210
    .word __extint_211
    .word __extint_212
    .word __extint_213
    .word __extint_214
    .word __extint_215
    .word __extint_216
    .word __extint_217
    .word __extint_218
    .word __extint_219
    .word __extint_220
    .word __extint_221
    .word __extint_222
    .word __extint_223
    .word __extint_224
    .word __extint_225
    .word __extint_226
    .word __extint_227
    .word __extint_228
    .word __extint_229
    .word __extint_230
    .word __extint_231
    .word __extint_232
    .word __extint_233
    .word __extint_234
    .word __extint_235
    .word __extint_236
    .word __extint_237
    .word __extint_238
    .word __extint_239
    .word __extint_240
    .word __extint_241
    .word __extint_242
    .word __extint_243
    .word __extint_244
    .word __extint_245
    .word __extint_246
    .word __extint_247
    .word __extint_248
    .word __extint_249
    .word __extint_250
    .word __extint_251
    .word __extint_252
    .word __extint_253
    .word __extint_254
    .word __extint_255

.section .boot_code

__rst_handler:
    b __kernel_init

/**
 * Initializes the CPU registers at boot time.
 */
__kernel_init:
    /* Init lo registers */
    eor r0, r0
    eor r1, r1
    eor r2, r2
    eor r3, r3
    eor r4, r4
    eor r5, r5
    eor r6, r6
    eor r7, r7
    
    /* Set stack */
    ldr r0, =MAIN_STACK_ADDRESS
    mov sp, r0

    /* Blank BSS */
    ldr r0, =_start_bss
    ldr r1, =_end_bss
    eor r2, r2
__kernel_bss_init:  
    cmp r0, r1 
    beq __kernel_bss_init_end

    str r2, [r0]
    add r0, r0, #4
    b __kernel_bss_init

__kernel_bss_init_end:

    /* Copy data from flash */
    ldr r0, =_start_data
    ldr r1, =_end_data
    ldr r2, =_start_init_data
__kernel_data_init:  
    cmp r0, r1 
    beq __kernel_data_init_end
    ldr r3, [r2]
    str r3, [r0]
    add r0, r0, #4
    add r2, r2, #4
    b __kernel_data_init
__kernel_data_init_end:

    /* Init FPU */
    bl __fpu_init

    /* Initializes NVIC */
    bl __nvic_init

    /* Call BSP initialization */
    bl __bsp_init   

    /* Call kernel kickstart entry point */    
    bl kernel_kickstart

    /* If we returned, raise a kernel panic */
    b kernel_panic


/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
