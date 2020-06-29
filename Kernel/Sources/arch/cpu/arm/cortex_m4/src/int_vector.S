/*******************************************************************************
 * @file int_vector.S
 *
 * @author Alexy Torres Aurora Dugo
 *
 * @date 28/06/2020
 *
 * @version 1.0
 *
 * @brief Kernel's interrupt vector handlers for the Cortex M4 CPU.
 *
 * @details Kernel's interrupt vector handlers for the Cortex M4 CPU.
 ******************************************************************************/
.syntax unified

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

/*******************************************************************************
 * MACRO DEFINE
 ******************************************************************************/

/*******************************************************************************
 * EXTERN DATA
 ******************************************************************************/

/*******************************************************************************
 * EXTERN FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/

.global __exc_nmi_handler
.global __exc_hardfault_handler
.global __exc_mpu_handler   
.global __exc_bus_handler
.global __exc_usage_handler
.global __exc_undef_handler
.global __exc_undef_handler
.global __exc_undef_handler
.global __exc_undef_handler
.global __exc_svc_handler
.global __exc_debug_handler
.global __exc_undef_handler
.global __exc_pensv_handler
.global __sys_tick_handler

.global __extint_0
.global __extint_1
.global __extint_2
.global __extint_3
.global __extint_4
.global __extint_5
.global __extint_6
.global __extint_7
.global __extint_8
.global __extint_9
.global __extint_10
.global __extint_11
.global __extint_12
.global __extint_13
.global __extint_14
.global __extint_15
.global __extint_16
.global __extint_17
.global __extint_18
.global __extint_19
.global __extint_20
.global __extint_21
.global __extint_22
.global __extint_23
.global __extint_24
.global __extint_25
.global __extint_26
.global __extint_27
.global __extint_28
.global __extint_29
.global __extint_30
.global __extint_31
.global __extint_32
.global __extint_33
.global __extint_34
.global __extint_35
.global __extint_36
.global __extint_37
.global __extint_38
.global __extint_39
.global __extint_40
.global __extint_41
.global __extint_42
.global __extint_43
.global __extint_44
.global __extint_45
.global __extint_46
.global __extint_47
.global __extint_48
.global __extint_49
.global __extint_50
.global __extint_51
.global __extint_52
.global __extint_53
.global __extint_54
.global __extint_55
.global __extint_56
.global __extint_57
.global __extint_58
.global __extint_59
.global __extint_60
.global __extint_61
.global __extint_62
.global __extint_63
.global __extint_64
.global __extint_65
.global __extint_66
.global __extint_67
.global __extint_68
.global __extint_69
.global __extint_70
.global __extint_71
.global __extint_72
.global __extint_73
.global __extint_74
.global __extint_75
.global __extint_76
.global __extint_77
.global __extint_78
.global __extint_79
.global __extint_80
.global __extint_81
.global __extint_82
.global __extint_83
.global __extint_84
.global __extint_85
.global __extint_86
.global __extint_87
.global __extint_88
.global __extint_89
.global __extint_90
.global __extint_91
.global __extint_92
.global __extint_93
.global __extint_94
.global __extint_95
.global __extint_96
.global __extint_97
.global __extint_98
.global __extint_99
.global __extint_100
.global __extint_101
.global __extint_102
.global __extint_103
.global __extint_104
.global __extint_105
.global __extint_106
.global __extint_107
.global __extint_108
.global __extint_109
.global __extint_110
.global __extint_111
.global __extint_112
.global __extint_113
.global __extint_114
.global __extint_115
.global __extint_116
.global __extint_117
.global __extint_118
.global __extint_119
.global __extint_120
.global __extint_121
.global __extint_122
.global __extint_123
.global __extint_124
.global __extint_125
.global __extint_126
.global __extint_127
.global __extint_128
.global __extint_129
.global __extint_130
.global __extint_131
.global __extint_132
.global __extint_133
.global __extint_134
.global __extint_135
.global __extint_136
.global __extint_137
.global __extint_138
.global __extint_139
.global __extint_140
.global __extint_141
.global __extint_142
.global __extint_143
.global __extint_144
.global __extint_145
.global __extint_146
.global __extint_147
.global __extint_148
.global __extint_149
.global __extint_150
.global __extint_151
.global __extint_152
.global __extint_153
.global __extint_154
.global __extint_155
.global __extint_156
.global __extint_157
.global __extint_158
.global __extint_159
.global __extint_160
.global __extint_161
.global __extint_162
.global __extint_163
.global __extint_164
.global __extint_165
.global __extint_166
.global __extint_167
.global __extint_168
.global __extint_169
.global __extint_170
.global __extint_171
.global __extint_172
.global __extint_173
.global __extint_174
.global __extint_175
.global __extint_176
.global __extint_177
.global __extint_178
.global __extint_179
.global __extint_180
.global __extint_181
.global __extint_182
.global __extint_183
.global __extint_184
.global __extint_185
.global __extint_186
.global __extint_187
.global __extint_188
.global __extint_189
.global __extint_190
.global __extint_191
.global __extint_192
.global __extint_193
.global __extint_194
.global __extint_195
.global __extint_196
.global __extint_197
.global __extint_198
.global __extint_199
.global __extint_200
.global __extint_201
.global __extint_202
.global __extint_203
.global __extint_204
.global __extint_205
.global __extint_206
.global __extint_207
.global __extint_208
.global __extint_209
.global __extint_210
.global __extint_211
.global __extint_212
.global __extint_213
.global __extint_214
.global __extint_215
.global __extint_216
.global __extint_217
.global __extint_218
.global __extint_219
.global __extint_220
.global __extint_221
.global __extint_222
.global __extint_223
.global __extint_224
.global __extint_225
.global __extint_226
.global __extint_227
.global __extint_228
.global __extint_229
.global __extint_230
.global __extint_231
.global __extint_232
.global __extint_233
.global __extint_234
.global __extint_235
.global __extint_236
.global __extint_237
.global __extint_238
.global __extint_239
.global __extint_240
.global __extint_241
.global __extint_242
.global __extint_243
.global __extint_244
.global __extint_245
.global __extint_246
.global __extint_247
.global __extint_248
.global __extint_249
.global __extint_250
.global __extint_251
.global __extint_252
.global __extint_253
.global __extint_254
.global __extint_255

/*******************************************************************************
 * CODE
 ******************************************************************************/
.section .text


__exc_nmi_handler:      
__exc_hardfault_handler:
__exc_mpu_handler:    
__exc_bus_handler:
__exc_usage_handler:
__exc_undef_handler:
__exc_undef_handler:
__exc_undef_handler:
__exc_undef_handler:
__exc_svc_handler:
__exc_debug_handler:
__exc_undef_handler:
__exc_pensv_handler:
__sys_tick_handler:

__extint_0:
__extint_1:
__extint_2:
__extint_3:
__extint_4:
__extint_5:
__extint_6:
__extint_7:
__extint_8:
__extint_9:
__extint_10:
__extint_11:
__extint_12:
__extint_13:
__extint_14:
__extint_15:
__extint_16:
__extint_17:
__extint_18:
__extint_19:
__extint_20:
__extint_21:
__extint_22:
__extint_23:
__extint_24:
__extint_25:
__extint_26:
__extint_27:
__extint_28:
__extint_29:
__extint_30:
__extint_31:
__extint_32:
__extint_33:
__extint_34:
__extint_35:
__extint_36:
__extint_37:
__extint_38:
__extint_39:
__extint_40:
__extint_41:
__extint_42:
__extint_43:
__extint_44:
__extint_45:
__extint_46:
__extint_47:
__extint_48:
__extint_49:
__extint_50:
__extint_51:
__extint_52:
__extint_53:
__extint_54:
__extint_55:
__extint_56:
__extint_57:
__extint_58:
__extint_59:
__extint_60:
__extint_61:
__extint_62:
__extint_63:
__extint_64:
__extint_65:
__extint_66:
__extint_67:
__extint_68:
__extint_69:
__extint_70:
__extint_71:
__extint_72:
__extint_73:
__extint_74:
__extint_75:
__extint_76:
__extint_77:
__extint_78:
__extint_79:
__extint_80:
__extint_81:
__extint_82:
__extint_83:
__extint_84:
__extint_85:
__extint_86:
__extint_87:
__extint_88:
__extint_89:
__extint_90:
__extint_91:
__extint_92:
__extint_93:
__extint_94:
__extint_95:
__extint_96:
__extint_97:
__extint_98:
__extint_99:
__extint_100:
__extint_101:
__extint_102:
__extint_103:
__extint_104:
__extint_105:
__extint_106:
__extint_107:
__extint_108:
__extint_109:
__extint_110:
__extint_111:
__extint_112:
__extint_113:
__extint_114:
__extint_115:
__extint_116:
__extint_117:
__extint_118:
__extint_119:
__extint_120:
__extint_121:
__extint_122:
__extint_123:
__extint_124:
__extint_125:
__extint_126:
__extint_127:
__extint_128:
__extint_129:
__extint_130:
__extint_131:
__extint_132:
__extint_133:
__extint_134:
__extint_135:
__extint_136:
__extint_137:
__extint_138:
__extint_139:
__extint_140:
__extint_141:
__extint_142:
__extint_143:
__extint_144:
__extint_145:
__extint_146:
__extint_147:
__extint_148:
__extint_149:
__extint_150:
__extint_151:
__extint_152:
__extint_153:
__extint_154:
__extint_155:
__extint_156:
__extint_157:
__extint_158:
__extint_159:
__extint_160:
__extint_161:
__extint_162:
__extint_163:
__extint_164:
__extint_165:
__extint_166:
__extint_167:
__extint_168:
__extint_169:
__extint_170:
__extint_171:
__extint_172:
__extint_173:
__extint_174:
__extint_175:
__extint_176:
__extint_177:
__extint_178:
__extint_179:
__extint_180:
__extint_181:
__extint_182:
__extint_183:
__extint_184:
__extint_185:
__extint_186:
__extint_187:
__extint_188:
__extint_189:
__extint_190:
__extint_191:
__extint_192:
__extint_193:
__extint_194:
__extint_195:
__extint_196:
__extint_197:
__extint_198:
__extint_199:
__extint_200:
__extint_201:
__extint_202:
__extint_203:
__extint_204:
__extint_205:
__extint_206:
__extint_207:
__extint_208:
__extint_209:
__extint_210:
__extint_211:
__extint_212:
__extint_213:
__extint_214:
__extint_215:
__extint_216:
__extint_217:
__extint_218:
__extint_219:
__extint_220:
__extint_221:
__extint_222:
__extint_223:
__extint_224:
__extint_225:
__extint_226:
__extint_227:
__extint_228:
__extint_229:
__extint_230:
__extint_231:
__extint_232:
__extint_233:
__extint_234:
__extint_235:
__extint_236:
__extint_237:
__extint_238:
__extint_239:
__extint_240:
__extint_241:
__extint_242:
__extint_243:
__extint_244:
__extint_245:
__extint_246:
__extint_247:
__extint_248:
__extint_249:
__extint_250:
__extint_251:
__extint_252:
__extint_253:
__extint_254:
__extint_255:

__placeholder_func:
    b __placeholder_func

/*******************************************************************************
 * DATA
 ******************************************************************************/
.section .data
