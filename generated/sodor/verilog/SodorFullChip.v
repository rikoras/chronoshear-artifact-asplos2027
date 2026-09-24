module CtlPath(
  input         clock,
  input         reset,
  input         io_dmem_resp_valid,
  input  [31:0] io_dat_dec_inst,
  input         io_dat_exe_br_eq,
  input         io_dat_exe_br_lt,
  input         io_dat_exe_br_ltu,
  input  [3:0]  io_dat_exe_br_type,
  input         io_dat_mem_ctrl_dmem_val,
  input         io_dat_csr_eret,
  output        io_ctl_dec_stall,
  output        io_ctl_full_stall,
  output [1:0]  io_ctl_exe_pc_sel,
  output [3:0]  io_ctl_br_type,
  output        io_ctl_if_kill,
  output        io_ctl_dec_kill,
  output [1:0]  io_ctl_op1_sel,
  output [2:0]  io_ctl_op2_sel,
  output [3:0]  io_ctl_alu_fun,
  output [1:0]  io_ctl_wb_sel,
  output        io_ctl_rf_wen,
  output        io_ctl_mem_val,
  output [1:0]  io_ctl_mem_fcn,
  output [2:0]  io_ctl_mem_typ,
  output [2:0]  io_ctl_csr_cmd,
  output        io_ctl_fencei,
  output        io_ctl_pipeline_kill,
  output        io_ctl_mem_exception
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
  reg [31:0] _RAND_2;
  reg [31:0] _RAND_3;
  reg [31:0] _RAND_4;
  reg [31:0] _RAND_5;
  reg [31:0] _RAND_6;
`endif // RANDOMIZE_REG_INIT
  wire [31:0] _csignals_T = io_dat_dec_inst & 32'h707f;
  wire [31:0] _csignals_T_16 = io_dat_dec_inst & 32'h7f;
  wire [31:0] _csignals_T_32 = io_dat_dec_inst & 32'hfc00707f;
  wire [31:0] _csignals_T_38 = io_dat_dec_inst & 32'hfe00707f;
  wire  _csignals_T_114 = 32'h4063 == _csignals_T | (32'h6063 == _csignals_T | (32'h5073 == _csignals_T | (32'h6073 ==
    _csignals_T | (32'h1073 == _csignals_T | (32'h2073 == _csignals_T | (32'h3073 == _csignals_T | (32'h7073 ==
    _csignals_T | (32'h73 == io_dat_dec_inst | (32'h30200073 == io_dat_dec_inst | (32'h7b200073 == io_dat_dec_inst | (32'h100073
     == io_dat_dec_inst | (32'h10500073 == io_dat_dec_inst | (32'h100f == _csignals_T | 32'hf == _csignals_T))))))))))))
    );
  wire  _csignals_T_129 = 32'h33 == _csignals_T_38 | (32'h40000033 == _csignals_T_38 | (32'h2033 == _csignals_T_38 | (32'h3033
     == _csignals_T_38 | (32'h7033 == _csignals_T_38 | (32'h6033 == _csignals_T_38 | (32'h4033 == _csignals_T_38 | (32'h40005033
     == _csignals_T_38 | (32'h5033 == _csignals_T_38 | (32'h6f == _csignals_T_16 | (32'h67 == _csignals_T | (32'h63 ==
    _csignals_T | (32'h1063 == _csignals_T | (32'h5063 == _csignals_T | (32'h7063 == _csignals_T | _csignals_T_114))))))
    ))))))));
  wire  _csignals_T_144 = 32'h2023 == _csignals_T | (32'h23 == _csignals_T | (32'h1023 == _csignals_T | (32'h17 ==
    _csignals_T_16 | (32'h37 == _csignals_T_16 | (32'h13 == _csignals_T | (32'h7013 == _csignals_T | (32'h6013 ==
    _csignals_T | (32'h4013 == _csignals_T | (32'h2013 == _csignals_T | (32'h3013 == _csignals_T | (32'h1013 ==
    _csignals_T_32 | (32'h40005013 == _csignals_T_32 | (32'h5013 == _csignals_T_32 | (32'h1033 == _csignals_T_38 |
    _csignals_T_129))))))))))))));
  wire  cs_val_inst = 32'h2003 == _csignals_T | (32'h3 == _csignals_T | (32'h4003 == _csignals_T | (32'h1003 ==
    _csignals_T | (32'h5003 == _csignals_T | _csignals_T_144))));
  wire [3:0] _csignals_T_162 = 32'h6063 == _csignals_T ? 4'h6 : 4'h0;
  wire [3:0] _csignals_T_163 = 32'h4063 == _csignals_T ? 4'h5 : _csignals_T_162;
  wire [3:0] _csignals_T_164 = 32'h7063 == _csignals_T ? 4'h4 : _csignals_T_163;
  wire [3:0] _csignals_T_165 = 32'h5063 == _csignals_T ? 4'h3 : _csignals_T_164;
  wire [3:0] _csignals_T_166 = 32'h1063 == _csignals_T ? 4'h1 : _csignals_T_165;
  wire [3:0] _csignals_T_167 = 32'h63 == _csignals_T ? 4'h2 : _csignals_T_166;
  wire [3:0] _csignals_T_168 = 32'h67 == _csignals_T ? 4'h8 : _csignals_T_167;
  wire [3:0] _csignals_T_169 = 32'h6f == _csignals_T_16 ? 4'h7 : _csignals_T_168;
  wire [3:0] _csignals_T_170 = 32'h5033 == _csignals_T_38 ? 4'h0 : _csignals_T_169;
  wire [3:0] _csignals_T_171 = 32'h40005033 == _csignals_T_38 ? 4'h0 : _csignals_T_170;
  wire [3:0] _csignals_T_172 = 32'h4033 == _csignals_T_38 ? 4'h0 : _csignals_T_171;
  wire [3:0] _csignals_T_173 = 32'h6033 == _csignals_T_38 ? 4'h0 : _csignals_T_172;
  wire [3:0] _csignals_T_174 = 32'h7033 == _csignals_T_38 ? 4'h0 : _csignals_T_173;
  wire [3:0] _csignals_T_175 = 32'h3033 == _csignals_T_38 ? 4'h0 : _csignals_T_174;
  wire [3:0] _csignals_T_176 = 32'h2033 == _csignals_T_38 ? 4'h0 : _csignals_T_175;
  wire [3:0] _csignals_T_177 = 32'h40000033 == _csignals_T_38 ? 4'h0 : _csignals_T_176;
  wire [3:0] _csignals_T_178 = 32'h33 == _csignals_T_38 ? 4'h0 : _csignals_T_177;
  wire [3:0] _csignals_T_179 = 32'h1033 == _csignals_T_38 ? 4'h0 : _csignals_T_178;
  wire [3:0] _csignals_T_180 = 32'h5013 == _csignals_T_32 ? 4'h0 : _csignals_T_179;
  wire [3:0] _csignals_T_181 = 32'h40005013 == _csignals_T_32 ? 4'h0 : _csignals_T_180;
  wire [3:0] _csignals_T_182 = 32'h1013 == _csignals_T_32 ? 4'h0 : _csignals_T_181;
  wire [3:0] _csignals_T_183 = 32'h3013 == _csignals_T ? 4'h0 : _csignals_T_182;
  wire [3:0] _csignals_T_184 = 32'h2013 == _csignals_T ? 4'h0 : _csignals_T_183;
  wire [3:0] _csignals_T_185 = 32'h4013 == _csignals_T ? 4'h0 : _csignals_T_184;
  wire [3:0] _csignals_T_186 = 32'h6013 == _csignals_T ? 4'h0 : _csignals_T_185;
  wire [3:0] _csignals_T_187 = 32'h7013 == _csignals_T ? 4'h0 : _csignals_T_186;
  wire [3:0] _csignals_T_188 = 32'h13 == _csignals_T ? 4'h0 : _csignals_T_187;
  wire [3:0] _csignals_T_189 = 32'h37 == _csignals_T_16 ? 4'h0 : _csignals_T_188;
  wire [3:0] _csignals_T_190 = 32'h17 == _csignals_T_16 ? 4'h0 : _csignals_T_189;
  wire [3:0] _csignals_T_191 = 32'h1023 == _csignals_T ? 4'h0 : _csignals_T_190;
  wire [3:0] _csignals_T_192 = 32'h23 == _csignals_T ? 4'h0 : _csignals_T_191;
  wire [3:0] _csignals_T_193 = 32'h2023 == _csignals_T ? 4'h0 : _csignals_T_192;
  wire [3:0] _csignals_T_194 = 32'h5003 == _csignals_T ? 4'h0 : _csignals_T_193;
  wire [3:0] _csignals_T_195 = 32'h1003 == _csignals_T ? 4'h0 : _csignals_T_194;
  wire [3:0] _csignals_T_196 = 32'h4003 == _csignals_T ? 4'h0 : _csignals_T_195;
  wire [3:0] _csignals_T_197 = 32'h3 == _csignals_T ? 4'h0 : _csignals_T_196;
  wire [1:0] _csignals_T_205 = 32'h7073 == _csignals_T ? 2'h2 : 2'h0;
  wire [1:0] _csignals_T_206 = 32'h3073 == _csignals_T ? 2'h0 : _csignals_T_205;
  wire [1:0] _csignals_T_207 = 32'h2073 == _csignals_T ? 2'h0 : _csignals_T_206;
  wire [1:0] _csignals_T_208 = 32'h1073 == _csignals_T ? 2'h0 : _csignals_T_207;
  wire [1:0] _csignals_T_209 = 32'h6073 == _csignals_T ? 2'h2 : _csignals_T_208;
  wire [1:0] _csignals_T_210 = 32'h5073 == _csignals_T ? 2'h2 : _csignals_T_209;
  wire [1:0] _csignals_T_211 = 32'h6063 == _csignals_T ? 2'h0 : _csignals_T_210;
  wire [1:0] _csignals_T_212 = 32'h4063 == _csignals_T ? 2'h0 : _csignals_T_211;
  wire [1:0] _csignals_T_213 = 32'h7063 == _csignals_T ? 2'h0 : _csignals_T_212;
  wire [1:0] _csignals_T_214 = 32'h5063 == _csignals_T ? 2'h0 : _csignals_T_213;
  wire [1:0] _csignals_T_215 = 32'h1063 == _csignals_T ? 2'h0 : _csignals_T_214;
  wire [1:0] _csignals_T_216 = 32'h63 == _csignals_T ? 2'h0 : _csignals_T_215;
  wire [1:0] _csignals_T_217 = 32'h67 == _csignals_T ? 2'h0 : _csignals_T_216;
  wire [1:0] _csignals_T_218 = 32'h6f == _csignals_T_16 ? 2'h0 : _csignals_T_217;
  wire [1:0] _csignals_T_219 = 32'h5033 == _csignals_T_38 ? 2'h0 : _csignals_T_218;
  wire [1:0] _csignals_T_220 = 32'h40005033 == _csignals_T_38 ? 2'h0 : _csignals_T_219;
  wire [1:0] _csignals_T_221 = 32'h4033 == _csignals_T_38 ? 2'h0 : _csignals_T_220;
  wire [1:0] _csignals_T_222 = 32'h6033 == _csignals_T_38 ? 2'h0 : _csignals_T_221;
  wire [1:0] _csignals_T_223 = 32'h7033 == _csignals_T_38 ? 2'h0 : _csignals_T_222;
  wire [1:0] _csignals_T_224 = 32'h3033 == _csignals_T_38 ? 2'h0 : _csignals_T_223;
  wire [1:0] _csignals_T_225 = 32'h2033 == _csignals_T_38 ? 2'h0 : _csignals_T_224;
  wire [1:0] _csignals_T_226 = 32'h40000033 == _csignals_T_38 ? 2'h0 : _csignals_T_225;
  wire [1:0] _csignals_T_227 = 32'h33 == _csignals_T_38 ? 2'h0 : _csignals_T_226;
  wire [1:0] _csignals_T_228 = 32'h1033 == _csignals_T_38 ? 2'h0 : _csignals_T_227;
  wire [1:0] _csignals_T_229 = 32'h5013 == _csignals_T_32 ? 2'h0 : _csignals_T_228;
  wire [1:0] _csignals_T_230 = 32'h40005013 == _csignals_T_32 ? 2'h0 : _csignals_T_229;
  wire [1:0] _csignals_T_231 = 32'h1013 == _csignals_T_32 ? 2'h0 : _csignals_T_230;
  wire [1:0] _csignals_T_232 = 32'h3013 == _csignals_T ? 2'h0 : _csignals_T_231;
  wire [1:0] _csignals_T_233 = 32'h2013 == _csignals_T ? 2'h0 : _csignals_T_232;
  wire [1:0] _csignals_T_234 = 32'h4013 == _csignals_T ? 2'h0 : _csignals_T_233;
  wire [1:0] _csignals_T_235 = 32'h6013 == _csignals_T ? 2'h0 : _csignals_T_234;
  wire [1:0] _csignals_T_236 = 32'h7013 == _csignals_T ? 2'h0 : _csignals_T_235;
  wire [1:0] _csignals_T_237 = 32'h13 == _csignals_T ? 2'h0 : _csignals_T_236;
  wire [1:0] _csignals_T_238 = 32'h37 == _csignals_T_16 ? 2'h0 : _csignals_T_237;
  wire [1:0] _csignals_T_239 = 32'h17 == _csignals_T_16 ? 2'h1 : _csignals_T_238;
  wire [1:0] _csignals_T_240 = 32'h1023 == _csignals_T ? 2'h0 : _csignals_T_239;
  wire [1:0] _csignals_T_241 = 32'h23 == _csignals_T ? 2'h0 : _csignals_T_240;
  wire [1:0] _csignals_T_242 = 32'h2023 == _csignals_T ? 2'h0 : _csignals_T_241;
  wire [1:0] _csignals_T_243 = 32'h5003 == _csignals_T ? 2'h0 : _csignals_T_242;
  wire [1:0] _csignals_T_244 = 32'h1003 == _csignals_T ? 2'h0 : _csignals_T_243;
  wire [1:0] _csignals_T_245 = 32'h4003 == _csignals_T ? 2'h0 : _csignals_T_244;
  wire [1:0] _csignals_T_246 = 32'h3 == _csignals_T ? 2'h0 : _csignals_T_245;
  wire [2:0] _csignals_T_260 = 32'h6063 == _csignals_T ? 3'h3 : 3'h0;
  wire [2:0] _csignals_T_261 = 32'h4063 == _csignals_T ? 3'h3 : _csignals_T_260;
  wire [2:0] _csignals_T_262 = 32'h7063 == _csignals_T ? 3'h3 : _csignals_T_261;
  wire [2:0] _csignals_T_263 = 32'h5063 == _csignals_T ? 3'h3 : _csignals_T_262;
  wire [2:0] _csignals_T_264 = 32'h1063 == _csignals_T ? 3'h3 : _csignals_T_263;
  wire [2:0] _csignals_T_265 = 32'h63 == _csignals_T ? 3'h3 : _csignals_T_264;
  wire [2:0] _csignals_T_266 = 32'h67 == _csignals_T ? 3'h1 : _csignals_T_265;
  wire [2:0] _csignals_T_267 = 32'h6f == _csignals_T_16 ? 3'h5 : _csignals_T_266;
  wire [2:0] _csignals_T_268 = 32'h5033 == _csignals_T_38 ? 3'h0 : _csignals_T_267;
  wire [2:0] _csignals_T_269 = 32'h40005033 == _csignals_T_38 ? 3'h0 : _csignals_T_268;
  wire [2:0] _csignals_T_270 = 32'h4033 == _csignals_T_38 ? 3'h0 : _csignals_T_269;
  wire [2:0] _csignals_T_271 = 32'h6033 == _csignals_T_38 ? 3'h0 : _csignals_T_270;
  wire [2:0] _csignals_T_272 = 32'h7033 == _csignals_T_38 ? 3'h0 : _csignals_T_271;
  wire [2:0] _csignals_T_273 = 32'h3033 == _csignals_T_38 ? 3'h0 : _csignals_T_272;
  wire [2:0] _csignals_T_274 = 32'h2033 == _csignals_T_38 ? 3'h0 : _csignals_T_273;
  wire [2:0] _csignals_T_275 = 32'h40000033 == _csignals_T_38 ? 3'h0 : _csignals_T_274;
  wire [2:0] _csignals_T_276 = 32'h33 == _csignals_T_38 ? 3'h0 : _csignals_T_275;
  wire [2:0] _csignals_T_277 = 32'h1033 == _csignals_T_38 ? 3'h0 : _csignals_T_276;
  wire [2:0] _csignals_T_278 = 32'h5013 == _csignals_T_32 ? 3'h1 : _csignals_T_277;
  wire [2:0] _csignals_T_279 = 32'h40005013 == _csignals_T_32 ? 3'h1 : _csignals_T_278;
  wire [2:0] _csignals_T_280 = 32'h1013 == _csignals_T_32 ? 3'h1 : _csignals_T_279;
  wire [2:0] _csignals_T_281 = 32'h3013 == _csignals_T ? 3'h1 : _csignals_T_280;
  wire [2:0] _csignals_T_282 = 32'h2013 == _csignals_T ? 3'h1 : _csignals_T_281;
  wire [2:0] _csignals_T_283 = 32'h4013 == _csignals_T ? 3'h1 : _csignals_T_282;
  wire [2:0] _csignals_T_284 = 32'h6013 == _csignals_T ? 3'h1 : _csignals_T_283;
  wire [2:0] _csignals_T_285 = 32'h7013 == _csignals_T ? 3'h1 : _csignals_T_284;
  wire [2:0] _csignals_T_286 = 32'h13 == _csignals_T ? 3'h1 : _csignals_T_285;
  wire [2:0] _csignals_T_287 = 32'h37 == _csignals_T_16 ? 3'h4 : _csignals_T_286;
  wire [2:0] _csignals_T_288 = 32'h17 == _csignals_T_16 ? 3'h4 : _csignals_T_287;
  wire [2:0] _csignals_T_289 = 32'h1023 == _csignals_T ? 3'h2 : _csignals_T_288;
  wire [2:0] _csignals_T_290 = 32'h23 == _csignals_T ? 3'h2 : _csignals_T_289;
  wire [2:0] _csignals_T_291 = 32'h2023 == _csignals_T ? 3'h2 : _csignals_T_290;
  wire [2:0] _csignals_T_292 = 32'h5003 == _csignals_T ? 3'h1 : _csignals_T_291;
  wire [2:0] _csignals_T_293 = 32'h1003 == _csignals_T ? 3'h1 : _csignals_T_292;
  wire [2:0] _csignals_T_294 = 32'h4003 == _csignals_T ? 3'h1 : _csignals_T_293;
  wire [2:0] _csignals_T_295 = 32'h3 == _csignals_T ? 3'h1 : _csignals_T_294;
  wire  _csignals_T_316 = 32'h6f == _csignals_T_16 ? 1'h0 : 32'h67 == _csignals_T | (32'h63 == _csignals_T | (32'h1063
     == _csignals_T | (32'h5063 == _csignals_T | (32'h7063 == _csignals_T | (32'h4063 == _csignals_T | (32'h6063 ==
    _csignals_T | (32'h5073 == _csignals_T | (32'h6073 == _csignals_T | (32'h1073 == _csignals_T | (32'h2073 ==
    _csignals_T | (32'h3073 == _csignals_T | 32'h7073 == _csignals_T)))))))))));
  wire  _csignals_T_331 = 32'h2013 == _csignals_T | (32'h3013 == _csignals_T | (32'h1013 == _csignals_T_32 | (32'h40005013
     == _csignals_T_32 | (32'h5013 == _csignals_T_32 | (32'h1033 == _csignals_T_38 | (32'h33 == _csignals_T_38 | (32'h40000033
     == _csignals_T_38 | (32'h2033 == _csignals_T_38 | (32'h3033 == _csignals_T_38 | (32'h7033 == _csignals_T_38 | (32'h6033
     == _csignals_T_38 | (32'h4033 == _csignals_T_38 | (32'h40005033 == _csignals_T_38 | (32'h5033 == _csignals_T_38 |
    _csignals_T_316))))))))))))));
  wire  _csignals_T_336 = 32'h37 == _csignals_T_16 ? 1'h0 : 32'h13 == _csignals_T | (32'h7013 == _csignals_T | (32'h6013
     == _csignals_T | (32'h4013 == _csignals_T | _csignals_T_331)));
  wire  _csignals_T_337 = 32'h17 == _csignals_T_16 ? 1'h0 : _csignals_T_336;
  wire  cs_rs1_oen = 32'h2003 == _csignals_T | (32'h3 == _csignals_T | (32'h4003 == _csignals_T | (32'h1003 ==
    _csignals_T | (32'h5003 == _csignals_T | (32'h2023 == _csignals_T | (32'h23 == _csignals_T | (32'h1023 ==
    _csignals_T | _csignals_T_337)))))));
  wire  _csignals_T_364 = 32'h67 == _csignals_T ? 1'h0 : 32'h63 == _csignals_T | (32'h1063 == _csignals_T | (32'h5063
     == _csignals_T | (32'h7063 == _csignals_T | (32'h4063 == _csignals_T | (32'h6063 == _csignals_T | (32'h5073 ==
    _csignals_T | (32'h6073 == _csignals_T | (32'h1073 == _csignals_T | (32'h2073 == _csignals_T | (32'h3073 ==
    _csignals_T | 32'h7073 == _csignals_T))))))))));
  wire  _csignals_T_365 = 32'h6f == _csignals_T_16 ? 1'h0 : _csignals_T_364;
  wire  _csignals_T_376 = 32'h5013 == _csignals_T_32 ? 1'h0 : 32'h1033 == _csignals_T_38 | (32'h33 == _csignals_T_38 | (32'h40000033
     == _csignals_T_38 | (32'h2033 == _csignals_T_38 | (32'h3033 == _csignals_T_38 | (32'h7033 == _csignals_T_38 | (32'h6033
     == _csignals_T_38 | (32'h4033 == _csignals_T_38 | (32'h40005033 == _csignals_T_38 | (32'h5033 == _csignals_T_38 |
    _csignals_T_365)))))))));
  wire  _csignals_T_377 = 32'h40005013 == _csignals_T_32 ? 1'h0 : _csignals_T_376;
  wire  _csignals_T_378 = 32'h1013 == _csignals_T_32 ? 1'h0 : _csignals_T_377;
  wire  _csignals_T_379 = 32'h3013 == _csignals_T ? 1'h0 : _csignals_T_378;
  wire  _csignals_T_380 = 32'h2013 == _csignals_T ? 1'h0 : _csignals_T_379;
  wire  _csignals_T_381 = 32'h4013 == _csignals_T ? 1'h0 : _csignals_T_380;
  wire  _csignals_T_382 = 32'h6013 == _csignals_T ? 1'h0 : _csignals_T_381;
  wire  _csignals_T_383 = 32'h7013 == _csignals_T ? 1'h0 : _csignals_T_382;
  wire  _csignals_T_384 = 32'h13 == _csignals_T ? 1'h0 : _csignals_T_383;
  wire  _csignals_T_385 = 32'h37 == _csignals_T_16 ? 1'h0 : _csignals_T_384;
  wire  _csignals_T_386 = 32'h17 == _csignals_T_16 ? 1'h0 : _csignals_T_385;
  wire  _csignals_T_390 = 32'h5003 == _csignals_T ? 1'h0 : 32'h2023 == _csignals_T | (32'h23 == _csignals_T | (32'h1023
     == _csignals_T | _csignals_T_386));
  wire  _csignals_T_391 = 32'h1003 == _csignals_T ? 1'h0 : _csignals_T_390;
  wire  _csignals_T_392 = 32'h4003 == _csignals_T ? 1'h0 : _csignals_T_391;
  wire  _csignals_T_393 = 32'h3 == _csignals_T ? 1'h0 : _csignals_T_392;
  wire  cs_rs2_oen = 32'h2003 == _csignals_T ? 1'h0 : _csignals_T_393;
  wire [3:0] _csignals_T_401 = 32'h7073 == _csignals_T ? 4'ha : 4'h0;
  wire [3:0] _csignals_T_402 = 32'h3073 == _csignals_T ? 4'ha : _csignals_T_401;
  wire [3:0] _csignals_T_403 = 32'h2073 == _csignals_T ? 4'ha : _csignals_T_402;
  wire [3:0] _csignals_T_404 = 32'h1073 == _csignals_T ? 4'ha : _csignals_T_403;
  wire [3:0] _csignals_T_405 = 32'h6073 == _csignals_T ? 4'ha : _csignals_T_404;
  wire [3:0] _csignals_T_406 = 32'h5073 == _csignals_T ? 4'ha : _csignals_T_405;
  wire [3:0] _csignals_T_407 = 32'h6063 == _csignals_T ? 4'h0 : _csignals_T_406;
  wire [3:0] _csignals_T_408 = 32'h4063 == _csignals_T ? 4'h0 : _csignals_T_407;
  wire [3:0] _csignals_T_409 = 32'h7063 == _csignals_T ? 4'h0 : _csignals_T_408;
  wire [3:0] _csignals_T_410 = 32'h5063 == _csignals_T ? 4'h0 : _csignals_T_409;
  wire [3:0] _csignals_T_411 = 32'h1063 == _csignals_T ? 4'h0 : _csignals_T_410;
  wire [3:0] _csignals_T_412 = 32'h63 == _csignals_T ? 4'h0 : _csignals_T_411;
  wire [3:0] _csignals_T_413 = 32'h67 == _csignals_T ? 4'h0 : _csignals_T_412;
  wire [3:0] _csignals_T_414 = 32'h6f == _csignals_T_16 ? 4'h0 : _csignals_T_413;
  wire [3:0] _csignals_T_415 = 32'h5033 == _csignals_T_38 ? 4'h3 : _csignals_T_414;
  wire [3:0] _csignals_T_416 = 32'h40005033 == _csignals_T_38 ? 4'h4 : _csignals_T_415;
  wire [3:0] _csignals_T_417 = 32'h4033 == _csignals_T_38 ? 4'h7 : _csignals_T_416;
  wire [3:0] _csignals_T_418 = 32'h6033 == _csignals_T_38 ? 4'h6 : _csignals_T_417;
  wire [3:0] _csignals_T_419 = 32'h7033 == _csignals_T_38 ? 4'h5 : _csignals_T_418;
  wire [3:0] _csignals_T_420 = 32'h3033 == _csignals_T_38 ? 4'h9 : _csignals_T_419;
  wire [3:0] _csignals_T_421 = 32'h2033 == _csignals_T_38 ? 4'h8 : _csignals_T_420;
  wire [3:0] _csignals_T_422 = 32'h40000033 == _csignals_T_38 ? 4'h1 : _csignals_T_421;
  wire [3:0] _csignals_T_423 = 32'h33 == _csignals_T_38 ? 4'h0 : _csignals_T_422;
  wire [3:0] _csignals_T_424 = 32'h1033 == _csignals_T_38 ? 4'h2 : _csignals_T_423;
  wire [3:0] _csignals_T_425 = 32'h5013 == _csignals_T_32 ? 4'h3 : _csignals_T_424;
  wire [3:0] _csignals_T_426 = 32'h40005013 == _csignals_T_32 ? 4'h4 : _csignals_T_425;
  wire [3:0] _csignals_T_427 = 32'h1013 == _csignals_T_32 ? 4'h2 : _csignals_T_426;
  wire [3:0] _csignals_T_428 = 32'h3013 == _csignals_T ? 4'h9 : _csignals_T_427;
  wire [3:0] _csignals_T_429 = 32'h2013 == _csignals_T ? 4'h8 : _csignals_T_428;
  wire [3:0] _csignals_T_430 = 32'h4013 == _csignals_T ? 4'h7 : _csignals_T_429;
  wire [3:0] _csignals_T_431 = 32'h6013 == _csignals_T ? 4'h6 : _csignals_T_430;
  wire [3:0] _csignals_T_432 = 32'h7013 == _csignals_T ? 4'h5 : _csignals_T_431;
  wire [3:0] _csignals_T_433 = 32'h13 == _csignals_T ? 4'h0 : _csignals_T_432;
  wire [3:0] _csignals_T_434 = 32'h37 == _csignals_T_16 ? 4'hb : _csignals_T_433;
  wire [3:0] _csignals_T_435 = 32'h17 == _csignals_T_16 ? 4'h0 : _csignals_T_434;
  wire [3:0] _csignals_T_436 = 32'h1023 == _csignals_T ? 4'h0 : _csignals_T_435;
  wire [3:0] _csignals_T_437 = 32'h23 == _csignals_T ? 4'h0 : _csignals_T_436;
  wire [3:0] _csignals_T_438 = 32'h2023 == _csignals_T ? 4'h0 : _csignals_T_437;
  wire [3:0] _csignals_T_439 = 32'h5003 == _csignals_T ? 4'h0 : _csignals_T_438;
  wire [3:0] _csignals_T_440 = 32'h1003 == _csignals_T ? 4'h0 : _csignals_T_439;
  wire [3:0] _csignals_T_441 = 32'h4003 == _csignals_T ? 4'h0 : _csignals_T_440;
  wire [3:0] _csignals_T_442 = 32'h3 == _csignals_T ? 4'h0 : _csignals_T_441;
  wire [1:0] _csignals_T_450 = 32'h7073 == _csignals_T ? 2'h3 : 2'h0;
  wire [1:0] _csignals_T_451 = 32'h3073 == _csignals_T ? 2'h3 : _csignals_T_450;
  wire [1:0] _csignals_T_452 = 32'h2073 == _csignals_T ? 2'h3 : _csignals_T_451;
  wire [1:0] _csignals_T_453 = 32'h1073 == _csignals_T ? 2'h3 : _csignals_T_452;
  wire [1:0] _csignals_T_454 = 32'h6073 == _csignals_T ? 2'h3 : _csignals_T_453;
  wire [1:0] _csignals_T_455 = 32'h5073 == _csignals_T ? 2'h3 : _csignals_T_454;
  wire [1:0] _csignals_T_456 = 32'h6063 == _csignals_T ? 2'h0 : _csignals_T_455;
  wire [1:0] _csignals_T_457 = 32'h4063 == _csignals_T ? 2'h0 : _csignals_T_456;
  wire [1:0] _csignals_T_458 = 32'h7063 == _csignals_T ? 2'h0 : _csignals_T_457;
  wire [1:0] _csignals_T_459 = 32'h5063 == _csignals_T ? 2'h0 : _csignals_T_458;
  wire [1:0] _csignals_T_460 = 32'h1063 == _csignals_T ? 2'h0 : _csignals_T_459;
  wire [1:0] _csignals_T_461 = 32'h63 == _csignals_T ? 2'h0 : _csignals_T_460;
  wire [1:0] _csignals_T_462 = 32'h67 == _csignals_T ? 2'h2 : _csignals_T_461;
  wire [1:0] _csignals_T_463 = 32'h6f == _csignals_T_16 ? 2'h2 : _csignals_T_462;
  wire [1:0] _csignals_T_464 = 32'h5033 == _csignals_T_38 ? 2'h0 : _csignals_T_463;
  wire [1:0] _csignals_T_465 = 32'h40005033 == _csignals_T_38 ? 2'h0 : _csignals_T_464;
  wire [1:0] _csignals_T_466 = 32'h4033 == _csignals_T_38 ? 2'h0 : _csignals_T_465;
  wire [1:0] _csignals_T_467 = 32'h6033 == _csignals_T_38 ? 2'h0 : _csignals_T_466;
  wire [1:0] _csignals_T_468 = 32'h7033 == _csignals_T_38 ? 2'h0 : _csignals_T_467;
  wire [1:0] _csignals_T_469 = 32'h3033 == _csignals_T_38 ? 2'h0 : _csignals_T_468;
  wire [1:0] _csignals_T_470 = 32'h2033 == _csignals_T_38 ? 2'h0 : _csignals_T_469;
  wire [1:0] _csignals_T_471 = 32'h40000033 == _csignals_T_38 ? 2'h0 : _csignals_T_470;
  wire [1:0] _csignals_T_472 = 32'h33 == _csignals_T_38 ? 2'h0 : _csignals_T_471;
  wire [1:0] _csignals_T_473 = 32'h1033 == _csignals_T_38 ? 2'h0 : _csignals_T_472;
  wire [1:0] _csignals_T_474 = 32'h5013 == _csignals_T_32 ? 2'h0 : _csignals_T_473;
  wire [1:0] _csignals_T_475 = 32'h40005013 == _csignals_T_32 ? 2'h0 : _csignals_T_474;
  wire [1:0] _csignals_T_476 = 32'h1013 == _csignals_T_32 ? 2'h0 : _csignals_T_475;
  wire [1:0] _csignals_T_477 = 32'h3013 == _csignals_T ? 2'h0 : _csignals_T_476;
  wire [1:0] _csignals_T_478 = 32'h2013 == _csignals_T ? 2'h0 : _csignals_T_477;
  wire [1:0] _csignals_T_479 = 32'h4013 == _csignals_T ? 2'h0 : _csignals_T_478;
  wire [1:0] _csignals_T_480 = 32'h6013 == _csignals_T ? 2'h0 : _csignals_T_479;
  wire [1:0] _csignals_T_481 = 32'h7013 == _csignals_T ? 2'h0 : _csignals_T_480;
  wire [1:0] _csignals_T_482 = 32'h13 == _csignals_T ? 2'h0 : _csignals_T_481;
  wire [1:0] _csignals_T_483 = 32'h37 == _csignals_T_16 ? 2'h0 : _csignals_T_482;
  wire [1:0] _csignals_T_484 = 32'h17 == _csignals_T_16 ? 2'h0 : _csignals_T_483;
  wire [1:0] _csignals_T_485 = 32'h1023 == _csignals_T ? 2'h0 : _csignals_T_484;
  wire [1:0] _csignals_T_486 = 32'h23 == _csignals_T ? 2'h0 : _csignals_T_485;
  wire [1:0] _csignals_T_487 = 32'h2023 == _csignals_T ? 2'h0 : _csignals_T_486;
  wire [1:0] _csignals_T_488 = 32'h5003 == _csignals_T ? 2'h1 : _csignals_T_487;
  wire [1:0] _csignals_T_489 = 32'h1003 == _csignals_T ? 2'h1 : _csignals_T_488;
  wire [1:0] _csignals_T_490 = 32'h4003 == _csignals_T ? 2'h1 : _csignals_T_489;
  wire [1:0] _csignals_T_491 = 32'h3 == _csignals_T ? 2'h1 : _csignals_T_490;
  wire  _csignals_T_505 = 32'h6063 == _csignals_T ? 1'h0 : 32'h5073 == _csignals_T | (32'h6073 == _csignals_T | (32'h1073
     == _csignals_T | (32'h2073 == _csignals_T | (32'h3073 == _csignals_T | 32'h7073 == _csignals_T))));
  wire  _csignals_T_506 = 32'h4063 == _csignals_T ? 1'h0 : _csignals_T_505;
  wire  _csignals_T_507 = 32'h7063 == _csignals_T ? 1'h0 : _csignals_T_506;
  wire  _csignals_T_508 = 32'h5063 == _csignals_T ? 1'h0 : _csignals_T_507;
  wire  _csignals_T_509 = 32'h1063 == _csignals_T ? 1'h0 : _csignals_T_508;
  wire  _csignals_T_510 = 32'h63 == _csignals_T ? 1'h0 : _csignals_T_509;
  wire  _csignals_T_525 = 32'h1013 == _csignals_T_32 | (32'h40005013 == _csignals_T_32 | (32'h5013 == _csignals_T_32 | (32'h1033
     == _csignals_T_38 | (32'h33 == _csignals_T_38 | (32'h40000033 == _csignals_T_38 | (32'h2033 == _csignals_T_38 | (32'h3033
     == _csignals_T_38 | (32'h7033 == _csignals_T_38 | (32'h6033 == _csignals_T_38 | (32'h4033 == _csignals_T_38 | (32'h40005033
     == _csignals_T_38 | (32'h5033 == _csignals_T_38 | (32'h6f == _csignals_T_16 | (32'h67 == _csignals_T |
    _csignals_T_510))))))))))))));
  wire  _csignals_T_534 = 32'h1023 == _csignals_T ? 1'h0 : 32'h17 == _csignals_T_16 | (32'h37 == _csignals_T_16 | (32'h13
     == _csignals_T | (32'h7013 == _csignals_T | (32'h6013 == _csignals_T | (32'h4013 == _csignals_T | (32'h2013 ==
    _csignals_T | (32'h3013 == _csignals_T | _csignals_T_525)))))));
  wire  _csignals_T_535 = 32'h23 == _csignals_T ? 1'h0 : _csignals_T_534;
  wire  _csignals_T_536 = 32'h2023 == _csignals_T ? 1'h0 : _csignals_T_535;
  wire  _csignals_T_542 = 32'h100f == _csignals_T ? 1'h0 : 32'hf == _csignals_T;
  wire  _csignals_T_543 = 32'h10500073 == io_dat_dec_inst ? 1'h0 : _csignals_T_542;
  wire  _csignals_T_544 = 32'h100073 == io_dat_dec_inst ? 1'h0 : _csignals_T_543;
  wire  _csignals_T_545 = 32'h7b200073 == io_dat_dec_inst ? 1'h0 : _csignals_T_544;
  wire  _csignals_T_546 = 32'h30200073 == io_dat_dec_inst ? 1'h0 : _csignals_T_545;
  wire  _csignals_T_547 = 32'h73 == io_dat_dec_inst ? 1'h0 : _csignals_T_546;
  wire  _csignals_T_548 = 32'h7073 == _csignals_T ? 1'h0 : _csignals_T_547;
  wire  _csignals_T_549 = 32'h3073 == _csignals_T ? 1'h0 : _csignals_T_548;
  wire  _csignals_T_550 = 32'h2073 == _csignals_T ? 1'h0 : _csignals_T_549;
  wire  _csignals_T_551 = 32'h1073 == _csignals_T ? 1'h0 : _csignals_T_550;
  wire  _csignals_T_552 = 32'h6073 == _csignals_T ? 1'h0 : _csignals_T_551;
  wire  _csignals_T_553 = 32'h5073 == _csignals_T ? 1'h0 : _csignals_T_552;
  wire  _csignals_T_554 = 32'h6063 == _csignals_T ? 1'h0 : _csignals_T_553;
  wire  _csignals_T_555 = 32'h4063 == _csignals_T ? 1'h0 : _csignals_T_554;
  wire  _csignals_T_556 = 32'h7063 == _csignals_T ? 1'h0 : _csignals_T_555;
  wire  _csignals_T_557 = 32'h5063 == _csignals_T ? 1'h0 : _csignals_T_556;
  wire  _csignals_T_558 = 32'h1063 == _csignals_T ? 1'h0 : _csignals_T_557;
  wire  _csignals_T_559 = 32'h63 == _csignals_T ? 1'h0 : _csignals_T_558;
  wire  _csignals_T_560 = 32'h67 == _csignals_T ? 1'h0 : _csignals_T_559;
  wire  _csignals_T_561 = 32'h6f == _csignals_T_16 ? 1'h0 : _csignals_T_560;
  wire  _csignals_T_562 = 32'h5033 == _csignals_T_38 ? 1'h0 : _csignals_T_561;
  wire  _csignals_T_563 = 32'h40005033 == _csignals_T_38 ? 1'h0 : _csignals_T_562;
  wire  _csignals_T_564 = 32'h4033 == _csignals_T_38 ? 1'h0 : _csignals_T_563;
  wire  _csignals_T_565 = 32'h6033 == _csignals_T_38 ? 1'h0 : _csignals_T_564;
  wire  _csignals_T_566 = 32'h7033 == _csignals_T_38 ? 1'h0 : _csignals_T_565;
  wire  _csignals_T_567 = 32'h3033 == _csignals_T_38 ? 1'h0 : _csignals_T_566;
  wire  _csignals_T_568 = 32'h2033 == _csignals_T_38 ? 1'h0 : _csignals_T_567;
  wire  _csignals_T_569 = 32'h40000033 == _csignals_T_38 ? 1'h0 : _csignals_T_568;
  wire  _csignals_T_570 = 32'h33 == _csignals_T_38 ? 1'h0 : _csignals_T_569;
  wire  _csignals_T_571 = 32'h1033 == _csignals_T_38 ? 1'h0 : _csignals_T_570;
  wire  _csignals_T_572 = 32'h5013 == _csignals_T_32 ? 1'h0 : _csignals_T_571;
  wire  _csignals_T_573 = 32'h40005013 == _csignals_T_32 ? 1'h0 : _csignals_T_572;
  wire  _csignals_T_574 = 32'h1013 == _csignals_T_32 ? 1'h0 : _csignals_T_573;
  wire  _csignals_T_575 = 32'h3013 == _csignals_T ? 1'h0 : _csignals_T_574;
  wire  _csignals_T_576 = 32'h2013 == _csignals_T ? 1'h0 : _csignals_T_575;
  wire  _csignals_T_577 = 32'h4013 == _csignals_T ? 1'h0 : _csignals_T_576;
  wire  _csignals_T_578 = 32'h6013 == _csignals_T ? 1'h0 : _csignals_T_577;
  wire  _csignals_T_579 = 32'h7013 == _csignals_T ? 1'h0 : _csignals_T_578;
  wire  _csignals_T_580 = 32'h13 == _csignals_T ? 1'h0 : _csignals_T_579;
  wire  _csignals_T_581 = 32'h37 == _csignals_T_16 ? 1'h0 : _csignals_T_580;
  wire  _csignals_T_582 = 32'h17 == _csignals_T_16 ? 1'h0 : _csignals_T_581;
  wire  cs0_3 = 32'h2003 == _csignals_T | (32'h3 == _csignals_T | (32'h4003 == _csignals_T | (32'h1003 == _csignals_T |
    (32'h5003 == _csignals_T | (32'h2023 == _csignals_T | (32'h23 == _csignals_T | (32'h1023 == _csignals_T |
    _csignals_T_582)))))));
  wire  _csignals_T_635 = 32'h5003 == _csignals_T ? 1'h0 : 32'h2023 == _csignals_T | (32'h23 == _csignals_T | 32'h1023
     == _csignals_T);
  wire  _csignals_T_636 = 32'h1003 == _csignals_T ? 1'h0 : _csignals_T_635;
  wire  _csignals_T_637 = 32'h4003 == _csignals_T ? 1'h0 : _csignals_T_636;
  wire  _csignals_T_638 = 32'h3 == _csignals_T ? 1'h0 : _csignals_T_637;
  wire  cs0_4 = 32'h2003 == _csignals_T ? 1'h0 : _csignals_T_638;
  wire [2:0] _csignals_T_681 = 32'h1023 == _csignals_T ? 3'h2 : 3'h0;
  wire [2:0] _csignals_T_682 = 32'h23 == _csignals_T ? 3'h1 : _csignals_T_681;
  wire [2:0] _csignals_T_683 = 32'h2023 == _csignals_T ? 3'h3 : _csignals_T_682;
  wire [2:0] _csignals_T_684 = 32'h5003 == _csignals_T ? 3'h6 : _csignals_T_683;
  wire [2:0] _csignals_T_685 = 32'h1003 == _csignals_T ? 3'h2 : _csignals_T_684;
  wire [2:0] _csignals_T_686 = 32'h4003 == _csignals_T ? 3'h5 : _csignals_T_685;
  wire [2:0] _csignals_T_687 = 32'h3 == _csignals_T ? 3'h1 : _csignals_T_686;
  wire [2:0] _csignals_T_691 = 32'h100073 == io_dat_dec_inst ? 3'h4 : 3'h0;
  wire [2:0] _csignals_T_692 = 32'h7b200073 == io_dat_dec_inst ? 3'h4 : _csignals_T_691;
  wire [2:0] _csignals_T_693 = 32'h30200073 == io_dat_dec_inst ? 3'h4 : _csignals_T_692;
  wire [2:0] _csignals_T_694 = 32'h73 == io_dat_dec_inst ? 3'h4 : _csignals_T_693;
  wire [2:0] _csignals_T_695 = 32'h7073 == _csignals_T ? 3'h3 : _csignals_T_694;
  wire [2:0] _csignals_T_696 = 32'h3073 == _csignals_T ? 3'h3 : _csignals_T_695;
  wire [2:0] _csignals_T_697 = 32'h2073 == _csignals_T ? 3'h2 : _csignals_T_696;
  wire [2:0] _csignals_T_698 = 32'h1073 == _csignals_T ? 3'h1 : _csignals_T_697;
  wire [2:0] _csignals_T_699 = 32'h6073 == _csignals_T ? 3'h2 : _csignals_T_698;
  wire [2:0] _csignals_T_700 = 32'h5073 == _csignals_T ? 3'h1 : _csignals_T_699;
  wire [2:0] _csignals_T_701 = 32'h6063 == _csignals_T ? 3'h0 : _csignals_T_700;
  wire [2:0] _csignals_T_702 = 32'h4063 == _csignals_T ? 3'h0 : _csignals_T_701;
  wire [2:0] _csignals_T_703 = 32'h7063 == _csignals_T ? 3'h0 : _csignals_T_702;
  wire [2:0] _csignals_T_704 = 32'h5063 == _csignals_T ? 3'h0 : _csignals_T_703;
  wire [2:0] _csignals_T_705 = 32'h1063 == _csignals_T ? 3'h0 : _csignals_T_704;
  wire [2:0] _csignals_T_706 = 32'h63 == _csignals_T ? 3'h0 : _csignals_T_705;
  wire [2:0] _csignals_T_707 = 32'h67 == _csignals_T ? 3'h0 : _csignals_T_706;
  wire [2:0] _csignals_T_708 = 32'h6f == _csignals_T_16 ? 3'h0 : _csignals_T_707;
  wire [2:0] _csignals_T_709 = 32'h5033 == _csignals_T_38 ? 3'h0 : _csignals_T_708;
  wire [2:0] _csignals_T_710 = 32'h40005033 == _csignals_T_38 ? 3'h0 : _csignals_T_709;
  wire [2:0] _csignals_T_711 = 32'h4033 == _csignals_T_38 ? 3'h0 : _csignals_T_710;
  wire [2:0] _csignals_T_712 = 32'h6033 == _csignals_T_38 ? 3'h0 : _csignals_T_711;
  wire [2:0] _csignals_T_713 = 32'h7033 == _csignals_T_38 ? 3'h0 : _csignals_T_712;
  wire [2:0] _csignals_T_714 = 32'h3033 == _csignals_T_38 ? 3'h0 : _csignals_T_713;
  wire [2:0] _csignals_T_715 = 32'h2033 == _csignals_T_38 ? 3'h0 : _csignals_T_714;
  wire [2:0] _csignals_T_716 = 32'h40000033 == _csignals_T_38 ? 3'h0 : _csignals_T_715;
  wire [2:0] _csignals_T_717 = 32'h33 == _csignals_T_38 ? 3'h0 : _csignals_T_716;
  wire [2:0] _csignals_T_718 = 32'h1033 == _csignals_T_38 ? 3'h0 : _csignals_T_717;
  wire [2:0] _csignals_T_719 = 32'h5013 == _csignals_T_32 ? 3'h0 : _csignals_T_718;
  wire [2:0] _csignals_T_720 = 32'h40005013 == _csignals_T_32 ? 3'h0 : _csignals_T_719;
  wire [2:0] _csignals_T_721 = 32'h1013 == _csignals_T_32 ? 3'h0 : _csignals_T_720;
  wire [2:0] _csignals_T_722 = 32'h3013 == _csignals_T ? 3'h0 : _csignals_T_721;
  wire [2:0] _csignals_T_723 = 32'h2013 == _csignals_T ? 3'h0 : _csignals_T_722;
  wire [2:0] _csignals_T_724 = 32'h4013 == _csignals_T ? 3'h0 : _csignals_T_723;
  wire [2:0] _csignals_T_725 = 32'h6013 == _csignals_T ? 3'h0 : _csignals_T_724;
  wire [2:0] _csignals_T_726 = 32'h7013 == _csignals_T ? 3'h0 : _csignals_T_725;
  wire [2:0] _csignals_T_727 = 32'h13 == _csignals_T ? 3'h0 : _csignals_T_726;
  wire [2:0] _csignals_T_728 = 32'h37 == _csignals_T_16 ? 3'h0 : _csignals_T_727;
  wire [2:0] _csignals_T_729 = 32'h17 == _csignals_T_16 ? 3'h0 : _csignals_T_728;
  wire [2:0] _csignals_T_730 = 32'h1023 == _csignals_T ? 3'h0 : _csignals_T_729;
  wire [2:0] _csignals_T_731 = 32'h23 == _csignals_T ? 3'h0 : _csignals_T_730;
  wire [2:0] _csignals_T_732 = 32'h2023 == _csignals_T ? 3'h0 : _csignals_T_731;
  wire [2:0] _csignals_T_733 = 32'h5003 == _csignals_T ? 3'h0 : _csignals_T_732;
  wire [2:0] _csignals_T_734 = 32'h1003 == _csignals_T ? 3'h0 : _csignals_T_733;
  wire [2:0] _csignals_T_735 = 32'h4003 == _csignals_T ? 3'h0 : _csignals_T_734;
  wire [2:0] _csignals_T_736 = 32'h3 == _csignals_T ? 3'h0 : _csignals_T_735;
  wire [2:0] cs0_6 = 32'h2003 == _csignals_T ? 3'h0 : _csignals_T_736;
  wire  _csignals_T_739 = 32'h10500073 == io_dat_dec_inst ? 1'h0 : 32'h100f == _csignals_T;
  wire  _csignals_T_740 = 32'h100073 == io_dat_dec_inst ? 1'h0 : _csignals_T_739;
  wire  _csignals_T_741 = 32'h7b200073 == io_dat_dec_inst ? 1'h0 : _csignals_T_740;
  wire  _csignals_T_742 = 32'h30200073 == io_dat_dec_inst ? 1'h0 : _csignals_T_741;
  wire  _csignals_T_743 = 32'h73 == io_dat_dec_inst ? 1'h0 : _csignals_T_742;
  wire  _csignals_T_744 = 32'h7073 == _csignals_T ? 1'h0 : _csignals_T_743;
  wire  _csignals_T_745 = 32'h3073 == _csignals_T ? 1'h0 : _csignals_T_744;
  wire  _csignals_T_746 = 32'h2073 == _csignals_T ? 1'h0 : _csignals_T_745;
  wire  _csignals_T_747 = 32'h1073 == _csignals_T ? 1'h0 : _csignals_T_746;
  wire  _csignals_T_748 = 32'h6073 == _csignals_T ? 1'h0 : _csignals_T_747;
  wire  _csignals_T_749 = 32'h5073 == _csignals_T ? 1'h0 : _csignals_T_748;
  wire  _csignals_T_750 = 32'h6063 == _csignals_T ? 1'h0 : _csignals_T_749;
  wire  _csignals_T_751 = 32'h4063 == _csignals_T ? 1'h0 : _csignals_T_750;
  wire  _csignals_T_752 = 32'h7063 == _csignals_T ? 1'h0 : _csignals_T_751;
  wire  _csignals_T_753 = 32'h5063 == _csignals_T ? 1'h0 : _csignals_T_752;
  wire  _csignals_T_754 = 32'h1063 == _csignals_T ? 1'h0 : _csignals_T_753;
  wire  _csignals_T_755 = 32'h63 == _csignals_T ? 1'h0 : _csignals_T_754;
  wire  _csignals_T_756 = 32'h67 == _csignals_T ? 1'h0 : _csignals_T_755;
  wire  _csignals_T_757 = 32'h6f == _csignals_T_16 ? 1'h0 : _csignals_T_756;
  wire  _csignals_T_758 = 32'h5033 == _csignals_T_38 ? 1'h0 : _csignals_T_757;
  wire  _csignals_T_759 = 32'h40005033 == _csignals_T_38 ? 1'h0 : _csignals_T_758;
  wire  _csignals_T_760 = 32'h4033 == _csignals_T_38 ? 1'h0 : _csignals_T_759;
  wire  _csignals_T_761 = 32'h6033 == _csignals_T_38 ? 1'h0 : _csignals_T_760;
  wire  _csignals_T_762 = 32'h7033 == _csignals_T_38 ? 1'h0 : _csignals_T_761;
  wire  _csignals_T_763 = 32'h3033 == _csignals_T_38 ? 1'h0 : _csignals_T_762;
  wire  _csignals_T_764 = 32'h2033 == _csignals_T_38 ? 1'h0 : _csignals_T_763;
  wire  _csignals_T_765 = 32'h40000033 == _csignals_T_38 ? 1'h0 : _csignals_T_764;
  wire  _csignals_T_766 = 32'h33 == _csignals_T_38 ? 1'h0 : _csignals_T_765;
  wire  _csignals_T_767 = 32'h1033 == _csignals_T_38 ? 1'h0 : _csignals_T_766;
  wire  _csignals_T_768 = 32'h5013 == _csignals_T_32 ? 1'h0 : _csignals_T_767;
  wire  _csignals_T_769 = 32'h40005013 == _csignals_T_32 ? 1'h0 : _csignals_T_768;
  wire  _csignals_T_770 = 32'h1013 == _csignals_T_32 ? 1'h0 : _csignals_T_769;
  wire  _csignals_T_771 = 32'h3013 == _csignals_T ? 1'h0 : _csignals_T_770;
  wire  _csignals_T_772 = 32'h2013 == _csignals_T ? 1'h0 : _csignals_T_771;
  wire  _csignals_T_773 = 32'h4013 == _csignals_T ? 1'h0 : _csignals_T_772;
  wire  _csignals_T_774 = 32'h6013 == _csignals_T ? 1'h0 : _csignals_T_773;
  wire  _csignals_T_775 = 32'h7013 == _csignals_T ? 1'h0 : _csignals_T_774;
  wire  _csignals_T_776 = 32'h13 == _csignals_T ? 1'h0 : _csignals_T_775;
  wire  _csignals_T_777 = 32'h37 == _csignals_T_16 ? 1'h0 : _csignals_T_776;
  wire  _csignals_T_778 = 32'h17 == _csignals_T_16 ? 1'h0 : _csignals_T_777;
  wire  _csignals_T_779 = 32'h1023 == _csignals_T ? 1'h0 : _csignals_T_778;
  wire  _csignals_T_780 = 32'h23 == _csignals_T ? 1'h0 : _csignals_T_779;
  wire  _csignals_T_781 = 32'h2023 == _csignals_T ? 1'h0 : _csignals_T_780;
  wire  _csignals_T_782 = 32'h5003 == _csignals_T ? 1'h0 : _csignals_T_781;
  wire  _csignals_T_783 = 32'h1003 == _csignals_T ? 1'h0 : _csignals_T_782;
  wire  _csignals_T_784 = 32'h4003 == _csignals_T ? 1'h0 : _csignals_T_783;
  wire  _csignals_T_785 = 32'h3 == _csignals_T ? 1'h0 : _csignals_T_784;
  wire  cs0_7 = 32'h2003 == _csignals_T ? 1'h0 : _csignals_T_785;
  wire [1:0] _ctrl_exe_pc_sel_T_3 = ~io_dat_exe_br_eq ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_5 = io_dat_exe_br_eq ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_8 = ~io_dat_exe_br_lt ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_11 = ~io_dat_exe_br_ltu ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_13 = io_dat_exe_br_lt ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_15 = io_dat_exe_br_ltu ? 2'h1 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_18 = io_dat_exe_br_type == 4'h8 ? 2'h2 : 2'h0;
  wire [1:0] _ctrl_exe_pc_sel_T_19 = io_dat_exe_br_type == 4'h7 ? 2'h1 : _ctrl_exe_pc_sel_T_18;
  wire [1:0] _ctrl_exe_pc_sel_T_20 = io_dat_exe_br_type == 4'h6 ? _ctrl_exe_pc_sel_T_15 : _ctrl_exe_pc_sel_T_19;
  wire [1:0] _ctrl_exe_pc_sel_T_21 = io_dat_exe_br_type == 4'h5 ? _ctrl_exe_pc_sel_T_13 : _ctrl_exe_pc_sel_T_20;
  wire [1:0] _ctrl_exe_pc_sel_T_22 = io_dat_exe_br_type == 4'h4 ? _ctrl_exe_pc_sel_T_11 : _ctrl_exe_pc_sel_T_21;
  wire [1:0] _ctrl_exe_pc_sel_T_23 = io_dat_exe_br_type == 4'h3 ? _ctrl_exe_pc_sel_T_8 : _ctrl_exe_pc_sel_T_22;
  wire [1:0] _ctrl_exe_pc_sel_T_24 = io_dat_exe_br_type == 4'h2 ? _ctrl_exe_pc_sel_T_5 : _ctrl_exe_pc_sel_T_23;
  wire [1:0] _ctrl_exe_pc_sel_T_25 = io_dat_exe_br_type == 4'h1 ? _ctrl_exe_pc_sel_T_3 : _ctrl_exe_pc_sel_T_24;
  wire [1:0] _ctrl_exe_pc_sel_T_26 = io_dat_exe_br_type == 4'h0 ? 2'h0 : _ctrl_exe_pc_sel_T_25;
  wire [1:0] ctrl_exe_pc_sel = io_ctl_pipeline_kill ? 2'h3 : _ctrl_exe_pc_sel_T_26;
  reg  ifkill_REG;
  wire  dec_exception = ~cs_val_inst;
  wire [4:0] dec_rs1_addr = io_dat_dec_inst[19:15];
  wire [4:0] dec_rs2_addr = io_dat_dec_inst[24:20];
  wire [4:0] dec_wbaddr = io_dat_dec_inst[11:7];
  wire  dec_rs1_oen = ctrl_exe_pc_sel != 2'h0 ? 1'h0 : cs_rs1_oen;
  wire  dec_rs2_oen = ctrl_exe_pc_sel != 2'h0 ? 1'h0 : cs_rs2_oen;
  reg [4:0] exe_reg_wbaddr;
  reg  exe_reg_exception;
  reg  exe_reg_is_csr;
  reg  exe_inst_is_load;
  wire  stall = exe_inst_is_load & exe_reg_wbaddr == dec_rs1_addr & exe_reg_wbaddr != 5'h0 & dec_rs1_oen |
    exe_inst_is_load & exe_reg_wbaddr == dec_rs2_addr & exe_reg_wbaddr != 5'h0 & dec_rs2_oen | exe_reg_is_csr;
  wire  full_stall = ~(io_dat_mem_ctrl_dmem_val & io_dmem_resp_valid | ~io_dat_mem_ctrl_dmem_val);
  reg  io_ctl_fencei_REG;
  reg  io_ctl_mem_exception_REG;
  wire  csr_ren = (cs0_6 == 3'h2 | cs0_6 == 3'h3) & dec_rs1_addr == 5'h0;
  assign io_ctl_dec_stall = exe_inst_is_load & exe_reg_wbaddr == dec_rs1_addr & exe_reg_wbaddr != 5'h0 & dec_rs1_oen |
    exe_inst_is_load & exe_reg_wbaddr == dec_rs2_addr & exe_reg_wbaddr != 5'h0 & dec_rs2_oen | exe_reg_is_csr;
  assign io_ctl_full_stall = ~(io_dat_mem_ctrl_dmem_val & io_dmem_resp_valid | ~io_dat_mem_ctrl_dmem_val);
  assign io_ctl_exe_pc_sel = io_ctl_pipeline_kill ? 2'h3 : _ctrl_exe_pc_sel_T_26;
  assign io_ctl_br_type = 32'h2003 == _csignals_T ? 4'h0 : _csignals_T_197;
  assign io_ctl_if_kill = ctrl_exe_pc_sel != 2'h0 | cs0_7 | ifkill_REG;
  assign io_ctl_dec_kill = ctrl_exe_pc_sel != 2'h0;
  assign io_ctl_op1_sel = 32'h2003 == _csignals_T ? 2'h0 : _csignals_T_246;
  assign io_ctl_op2_sel = 32'h2003 == _csignals_T ? 3'h1 : _csignals_T_295;
  assign io_ctl_alu_fun = 32'h2003 == _csignals_T ? 4'h0 : _csignals_T_442;
  assign io_ctl_wb_sel = 32'h2003 == _csignals_T ? 2'h1 : _csignals_T_491;
  assign io_ctl_rf_wen = 32'h2003 == _csignals_T | (32'h3 == _csignals_T | (32'h4003 == _csignals_T | (32'h1003 ==
    _csignals_T | (32'h5003 == _csignals_T | _csignals_T_536))));
  assign io_ctl_mem_val = 32'h2003 == _csignals_T | (32'h3 == _csignals_T | (32'h4003 == _csignals_T | (32'h1003 ==
    _csignals_T | (32'h5003 == _csignals_T | (32'h2023 == _csignals_T | (32'h23 == _csignals_T | (32'h1023 ==
    _csignals_T | _csignals_T_582)))))));
  assign io_ctl_mem_fcn = {{1'd0}, cs0_4};
  assign io_ctl_mem_typ = 32'h2003 == _csignals_T ? 3'h3 : _csignals_T_687;
  assign io_ctl_csr_cmd = csr_ren ? 3'h5 : cs0_6;
  assign io_ctl_fencei = cs0_7 | io_ctl_fencei_REG;
  assign io_ctl_pipeline_kill = io_dat_csr_eret | io_ctl_mem_exception;
  assign io_ctl_mem_exception = io_ctl_mem_exception_REG;
  always @(posedge clock) begin
    if (32'h2003 == _csignals_T) begin
      ifkill_REG <= 1'h0;
    end else if (32'h3 == _csignals_T) begin
      ifkill_REG <= 1'h0;
    end else if (32'h4003 == _csignals_T) begin
      ifkill_REG <= 1'h0;
    end else if (32'h1003 == _csignals_T) begin
      ifkill_REG <= 1'h0;
    end else begin
      ifkill_REG <= _csignals_T_782;
    end
    if (~stall & ~full_stall) begin
      if (ctrl_exe_pc_sel != 2'h0) begin
        exe_reg_wbaddr <= 5'h0;
      end else begin
        exe_reg_wbaddr <= dec_wbaddr;
      end
    end else if (stall & ~full_stall) begin
      exe_reg_wbaddr <= 5'h0;
    end
    if (reset) begin
      exe_reg_exception <= 1'h0;
    end else if (~stall & ~full_stall) begin
      if (ctrl_exe_pc_sel != 2'h0) begin
        exe_reg_exception <= 1'h0;
      end else begin
        exe_reg_exception <= dec_exception;
      end
    end else if (stall & ~full_stall) begin
      exe_reg_exception <= 1'h0;
    end
    if (reset) begin
      exe_reg_is_csr <= 1'h0;
    end else if (~stall & ~full_stall) begin
      if (ctrl_exe_pc_sel != 2'h0) begin
        exe_reg_is_csr <= 1'h0;
      end else begin
        exe_reg_is_csr <= cs0_6 != 3'h0 & cs0_6 != 3'h4;
      end
    end else if (stall & ~full_stall) begin
      exe_reg_is_csr <= 1'h0;
    end
    if (reset) begin
      exe_inst_is_load <= 1'h0;
    end else if (~full_stall) begin
      exe_inst_is_load <= cs0_3 & ~cs0_4;
    end
    if (32'h2003 == _csignals_T) begin
      io_ctl_fencei_REG <= 1'h0;
    end else if (32'h3 == _csignals_T) begin
      io_ctl_fencei_REG <= 1'h0;
    end else if (32'h4003 == _csignals_T) begin
      io_ctl_fencei_REG <= 1'h0;
    end else if (32'h1003 == _csignals_T) begin
      io_ctl_fencei_REG <= 1'h0;
    end else begin
      io_ctl_fencei_REG <= _csignals_T_782;
    end
    io_ctl_mem_exception_REG <= exe_reg_exception;
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  ifkill_REG = _RAND_0[0:0];
  _RAND_1 = {1{`RANDOM}};
  exe_reg_wbaddr = _RAND_1[4:0];
  _RAND_2 = {1{`RANDOM}};
  exe_reg_exception = _RAND_2[0:0];
  _RAND_3 = {1{`RANDOM}};
  exe_reg_is_csr = _RAND_3[0:0];
  _RAND_4 = {1{`RANDOM}};
  exe_inst_is_load = _RAND_4[0:0];
  _RAND_5 = {1{`RANDOM}};
  io_ctl_fencei_REG = _RAND_5[0:0];
  _RAND_6 = {1{`RANDOM}};
  io_ctl_mem_exception_REG = _RAND_6[0:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module CSRFile(
  input         clock,
  input         reset,
  input  [2:0]  io_rw_cmd,
  output [31:0] io_rw_rdata,
  input  [31:0] io_rw_wdata,
  output        io_eret,
  input  [11:0] io_decode_csr,
  output        io_status_debug,
  output [1:0]  io_status_prv,
  output        io_status_sd,
  output [7:0]  io_status_zero1,
  output        io_status_tsr,
  output        io_status_tw,
  output        io_status_tvm,
  output        io_status_mxr,
  output        io_status_sum,
  output        io_status_mprv,
  output [1:0]  io_status_xs,
  output [1:0]  io_status_fs,
  output [1:0]  io_status_mpp,
  output [1:0]  io_status_hpp,
  output        io_status_spp,
  output        io_status_mpie,
  output        io_status_hpie,
  output        io_status_spie,
  output        io_status_upie,
  output        io_status_mie,
  output        io_status_hie,
  output        io_status_sie,
  output        io_status_uie,
  output [31:0] io_evec,
  input         io_exception,
  input         io_retire,
  input  [31:0] io_pc
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
  reg [31:0] _RAND_2;
  reg [31:0] _RAND_3;
  reg [31:0] _RAND_4;
  reg [31:0] _RAND_5;
  reg [31:0] _RAND_6;
  reg [31:0] _RAND_7;
  reg [31:0] _RAND_8;
  reg [31:0] _RAND_9;
  reg [31:0] _RAND_10;
  reg [31:0] _RAND_11;
  reg [63:0] _RAND_12;
  reg [31:0] _RAND_13;
  reg [63:0] _RAND_14;
  reg [63:0] _RAND_15;
  reg [63:0] _RAND_16;
  reg [63:0] _RAND_17;
  reg [63:0] _RAND_18;
  reg [63:0] _RAND_19;
  reg [63:0] _RAND_20;
  reg [63:0] _RAND_21;
  reg [63:0] _RAND_22;
  reg [63:0] _RAND_23;
  reg [63:0] _RAND_24;
  reg [63:0] _RAND_25;
  reg [63:0] _RAND_26;
  reg [63:0] _RAND_27;
  reg [63:0] _RAND_28;
  reg [63:0] _RAND_29;
  reg [63:0] _RAND_30;
  reg [63:0] _RAND_31;
  reg [63:0] _RAND_32;
  reg [63:0] _RAND_33;
  reg [63:0] _RAND_34;
  reg [63:0] _RAND_35;
  reg [63:0] _RAND_36;
  reg [63:0] _RAND_37;
  reg [63:0] _RAND_38;
  reg [63:0] _RAND_39;
  reg [63:0] _RAND_40;
  reg [63:0] _RAND_41;
  reg [63:0] _RAND_42;
  reg [63:0] _RAND_43;
  reg [63:0] _RAND_44;
  reg [63:0] _RAND_45;
  reg [63:0] _RAND_46;
  reg [31:0] _RAND_47;
  reg [31:0] _RAND_48;
  reg [31:0] _RAND_49;
  reg [31:0] _RAND_50;
`endif // RANDOMIZE_REG_INIT
  reg  reg_mstatus_mpie;
  reg  reg_mstatus_mie;
  reg [31:0] reg_mepc;
  reg [31:0] reg_mcause;
  reg [31:0] reg_mtval;
  reg [31:0] reg_mscratch;
  reg [31:0] reg_medeleg;
  reg  reg_mip_mtip;
  reg  reg_mip_msip;
  reg  reg_mie_mtip;
  reg  reg_mie_msip;
  reg [5:0] small_;
  wire [6:0] nextSmall = small_ + 6'h1;
  reg [57:0] large_;
  wire [57:0] _large_r_T_1 = large_ + 58'h1;
  wire [57:0] _GEN_0 = nextSmall[6] ? _large_r_T_1 : large_; // @[]
  wire [63:0] value = {large_,small_};
  reg [5:0] small_1;
  wire [5:0] _GEN_150 = {{5'd0}, io_retire};
  wire [6:0] nextSmall_1 = small_1 + _GEN_150;
  reg [57:0] large_1;
  wire [57:0] _large_r_T_3 = large_1 + 58'h1;
  wire [57:0] _GEN_1 = nextSmall_1[6] ? _large_r_T_3 : large_1; // @[]
  wire [63:0] value_1 = {large_1,small_1};
  reg [39:0] small_2;
  wire [40:0] nextSmall_2 = {{1'd0}, small_2};
  reg [39:0] small_3;
  wire [40:0] nextSmall_3 = {{1'd0}, small_3};
  reg [39:0] small_4;
  wire [40:0] nextSmall_4 = {{1'd0}, small_4};
  reg [39:0] small_5;
  wire [40:0] nextSmall_5 = {{1'd0}, small_5};
  reg [39:0] small_6;
  wire [40:0] nextSmall_6 = {{1'd0}, small_6};
  reg [39:0] small_7;
  wire [40:0] nextSmall_7 = {{1'd0}, small_7};
  reg [39:0] small_8;
  wire [40:0] nextSmall_8 = {{1'd0}, small_8};
  reg [39:0] small_9;
  wire [40:0] nextSmall_9 = {{1'd0}, small_9};
  reg [39:0] small_10;
  wire [40:0] nextSmall_10 = {{1'd0}, small_10};
  reg [39:0] small_11;
  wire [40:0] nextSmall_11 = {{1'd0}, small_11};
  reg [39:0] small_12;
  wire [40:0] nextSmall_12 = {{1'd0}, small_12};
  reg [39:0] small_13;
  wire [40:0] nextSmall_13 = {{1'd0}, small_13};
  reg [39:0] small_14;
  wire [40:0] nextSmall_14 = {{1'd0}, small_14};
  reg [39:0] small_15;
  wire [40:0] nextSmall_15 = {{1'd0}, small_15};
  reg [39:0] small_16;
  wire [40:0] nextSmall_16 = {{1'd0}, small_16};
  reg [39:0] small_17;
  wire [40:0] nextSmall_17 = {{1'd0}, small_17};
  reg [39:0] small_18;
  wire [40:0] nextSmall_18 = {{1'd0}, small_18};
  reg [39:0] small_19;
  wire [40:0] nextSmall_19 = {{1'd0}, small_19};
  reg [39:0] small_20;
  wire [40:0] nextSmall_20 = {{1'd0}, small_20};
  reg [39:0] small_21;
  wire [40:0] nextSmall_21 = {{1'd0}, small_21};
  reg [39:0] small_22;
  wire [40:0] nextSmall_22 = {{1'd0}, small_22};
  reg [39:0] small_23;
  wire [40:0] nextSmall_23 = {{1'd0}, small_23};
  reg [39:0] small_24;
  wire [40:0] nextSmall_24 = {{1'd0}, small_24};
  reg [39:0] small_25;
  wire [40:0] nextSmall_25 = {{1'd0}, small_25};
  reg [39:0] small_26;
  wire [40:0] nextSmall_26 = {{1'd0}, small_26};
  reg [39:0] small_27;
  wire [40:0] nextSmall_27 = {{1'd0}, small_27};
  reg [39:0] small_28;
  wire [40:0] nextSmall_28 = {{1'd0}, small_28};
  reg [39:0] small_29;
  wire [40:0] nextSmall_29 = {{1'd0}, small_29};
  reg [39:0] small_30;
  wire [40:0] nextSmall_30 = {{1'd0}, small_30};
  reg [39:0] small_31;
  wire [40:0] nextSmall_31 = {{1'd0}, small_31};
  reg [39:0] small_32;
  wire [40:0] nextSmall_32 = {{1'd0}, small_32};
  reg [39:0] small_33;
  wire [40:0] nextSmall_33 = {{1'd0}, small_33};
  reg [31:0] reg_dpc;
  reg [31:0] reg_dscratch;
  reg  reg_dcsr_ebreakm;
  reg  reg_dcsr_step;
  wire  system_insn = io_rw_cmd == 3'h4;
  wire  cpu_ren = io_rw_cmd != 3'h0 & ~system_insn;
  wire [4:0] read_mstatus_lo_lo = {io_status_upie,io_status_mie,io_status_hie,io_status_sie,io_status_uie};
  wire [12:0] read_mstatus_lo = {io_status_mpp,io_status_hpp,io_status_spp,io_status_mpie,io_status_hpie,io_status_spie,
    read_mstatus_lo_lo};
  wire [7:0] read_mstatus_hi_lo = {io_status_tvm,io_status_mxr,io_status_sum,io_status_mprv,io_status_xs,io_status_fs};
  wire [34:0] read_mstatus = {io_status_debug,io_status_prv,io_status_sd,io_status_zero1,io_status_tsr,io_status_tw,
    read_mstatus_hi_lo,read_mstatus_lo};
  wire [15:0] _T = {8'h0,reg_mip_mtip,1'h0,2'h0,reg_mip_msip,1'h0,2'h0};
  wire [15:0] _T_1 = {8'h0,reg_mie_mtip,1'h0,2'h0,reg_mie_msip,1'h0,2'h0};
  wire [31:0] _T_2 = {4'h4,12'h0,reg_dcsr_ebreakm,4'h0,6'h0,2'h0,reg_dcsr_step,2'h3};
  wire  read_only = &io_decode_csr[11:10];
  wire  cpu_wen = cpu_ren & io_rw_cmd != 3'h5;
  wire  wen = cpu_wen & ~read_only;
  wire [7:0] opcode = 8'h1 << io_decode_csr[2:0];
  wire  insn_call = system_insn & opcode[0];
  wire  insn_break = system_insn & opcode[1];
  wire  insn_ret = system_insn & opcode[2];
  wire [31:0] _GEN_2 = io_exception ? 32'h2 : reg_mcause; // @[]
  wire [31:0] _GEN_6 = insn_ret & io_decode_csr[10] ? reg_dpc : 32'h80000004; // @[]
  wire  _GEN_7 = insn_ret & ~io_decode_csr[10] ? reg_mstatus_mpie : reg_mstatus_mie; // @[]
  wire [31:0] _GEN_11 = insn_call ? 32'hb : _GEN_2; // @[]
  wire [31:0] _GEN_12 = insn_break ? 32'h3 : _GEN_11; // @[]
  wire [31:0] _GEN_13 = io_exception | insn_call | insn_break ? io_pc : reg_mepc; // @[]
  wire [63:0] _io_rw_rdata_T = io_decode_csr == 12'hb00 ? value : 64'h0;
  wire [63:0] _io_rw_rdata_T_1 = io_decode_csr == 12'hb02 ? value_1 : 64'h0;
  wire [15:0] _io_rw_rdata_T_2 = io_decode_csr == 12'hf13 ? 16'h8000 : 16'h0;
  wire [8:0] _io_rw_rdata_T_5 = io_decode_csr == 12'h301 ? 9'h100 : 9'h0;
  wire [34:0] _io_rw_rdata_T_6 = io_decode_csr == 12'h300 ? read_mstatus : 35'h0;
  wire [8:0] _io_rw_rdata_T_7 = io_decode_csr == 12'h305 ? 9'h100 : 9'h0;
  wire [15:0] _io_rw_rdata_T_8 = io_decode_csr == 12'h344 ? _T : 16'h0;
  wire [15:0] _io_rw_rdata_T_9 = io_decode_csr == 12'h304 ? _T_1 : 16'h0;
  wire [31:0] _io_rw_rdata_T_10 = io_decode_csr == 12'h340 ? reg_mscratch : 32'h0;
  wire [31:0] _io_rw_rdata_T_11 = io_decode_csr == 12'h341 ? reg_mepc : 32'h0;
  wire [31:0] _io_rw_rdata_T_12 = io_decode_csr == 12'h343 ? reg_mtval : 32'h0;
  wire [31:0] _io_rw_rdata_T_13 = io_decode_csr == 12'h342 ? reg_mcause : 32'h0;
  wire [31:0] _io_rw_rdata_T_15 = io_decode_csr == 12'h7b0 ? _T_2 : 32'h0;
  wire [31:0] _io_rw_rdata_T_16 = io_decode_csr == 12'h7b1 ? reg_dpc : 32'h0;
  wire [31:0] _io_rw_rdata_T_17 = io_decode_csr == 12'h7b2 ? reg_dscratch : 32'h0;
  wire [31:0] _io_rw_rdata_T_18 = io_decode_csr == 12'h302 ? reg_medeleg : 32'h0;
  wire [39:0] _io_rw_rdata_T_19 = io_decode_csr == 12'hb03 ? small_2 : 40'h0;
  wire [39:0] _io_rw_rdata_T_20 = io_decode_csr == 12'hb83 ? small_2 : 40'h0;
  wire [39:0] _io_rw_rdata_T_21 = io_decode_csr == 12'hb04 ? small_3 : 40'h0;
  wire [39:0] _io_rw_rdata_T_22 = io_decode_csr == 12'hb84 ? small_3 : 40'h0;
  wire [39:0] _io_rw_rdata_T_23 = io_decode_csr == 12'hb05 ? small_4 : 40'h0;
  wire [39:0] _io_rw_rdata_T_24 = io_decode_csr == 12'hb85 ? small_4 : 40'h0;
  wire [39:0] _io_rw_rdata_T_25 = io_decode_csr == 12'hb06 ? small_5 : 40'h0;
  wire [39:0] _io_rw_rdata_T_26 = io_decode_csr == 12'hb86 ? small_5 : 40'h0;
  wire [39:0] _io_rw_rdata_T_27 = io_decode_csr == 12'hb07 ? small_6 : 40'h0;
  wire [39:0] _io_rw_rdata_T_28 = io_decode_csr == 12'hb87 ? small_6 : 40'h0;
  wire [39:0] _io_rw_rdata_T_29 = io_decode_csr == 12'hb08 ? small_7 : 40'h0;
  wire [39:0] _io_rw_rdata_T_30 = io_decode_csr == 12'hb88 ? small_7 : 40'h0;
  wire [39:0] _io_rw_rdata_T_31 = io_decode_csr == 12'hb09 ? small_8 : 40'h0;
  wire [39:0] _io_rw_rdata_T_32 = io_decode_csr == 12'hb89 ? small_8 : 40'h0;
  wire [39:0] _io_rw_rdata_T_33 = io_decode_csr == 12'hb0a ? small_9 : 40'h0;
  wire [39:0] _io_rw_rdata_T_34 = io_decode_csr == 12'hb8a ? small_9 : 40'h0;
  wire [39:0] _io_rw_rdata_T_35 = io_decode_csr == 12'hb0b ? small_10 : 40'h0;
  wire [39:0] _io_rw_rdata_T_36 = io_decode_csr == 12'hb8b ? small_10 : 40'h0;
  wire [39:0] _io_rw_rdata_T_37 = io_decode_csr == 12'hb0c ? small_11 : 40'h0;
  wire [39:0] _io_rw_rdata_T_38 = io_decode_csr == 12'hb8c ? small_11 : 40'h0;
  wire [39:0] _io_rw_rdata_T_39 = io_decode_csr == 12'hb0d ? small_12 : 40'h0;
  wire [39:0] _io_rw_rdata_T_40 = io_decode_csr == 12'hb8d ? small_12 : 40'h0;
  wire [39:0] _io_rw_rdata_T_41 = io_decode_csr == 12'hb0e ? small_13 : 40'h0;
  wire [39:0] _io_rw_rdata_T_42 = io_decode_csr == 12'hb8e ? small_13 : 40'h0;
  wire [39:0] _io_rw_rdata_T_43 = io_decode_csr == 12'hb0f ? small_14 : 40'h0;
  wire [39:0] _io_rw_rdata_T_44 = io_decode_csr == 12'hb8f ? small_14 : 40'h0;
  wire [39:0] _io_rw_rdata_T_45 = io_decode_csr == 12'hb10 ? small_15 : 40'h0;
  wire [39:0] _io_rw_rdata_T_46 = io_decode_csr == 12'hb90 ? small_15 : 40'h0;
  wire [39:0] _io_rw_rdata_T_47 = io_decode_csr == 12'hb11 ? small_16 : 40'h0;
  wire [39:0] _io_rw_rdata_T_48 = io_decode_csr == 12'hb91 ? small_16 : 40'h0;
  wire [39:0] _io_rw_rdata_T_49 = io_decode_csr == 12'hb12 ? small_17 : 40'h0;
  wire [39:0] _io_rw_rdata_T_50 = io_decode_csr == 12'hb92 ? small_17 : 40'h0;
  wire [39:0] _io_rw_rdata_T_51 = io_decode_csr == 12'hb13 ? small_18 : 40'h0;
  wire [39:0] _io_rw_rdata_T_52 = io_decode_csr == 12'hb93 ? small_18 : 40'h0;
  wire [39:0] _io_rw_rdata_T_53 = io_decode_csr == 12'hb14 ? small_19 : 40'h0;
  wire [39:0] _io_rw_rdata_T_54 = io_decode_csr == 12'hb94 ? small_19 : 40'h0;
  wire [39:0] _io_rw_rdata_T_55 = io_decode_csr == 12'hb15 ? small_20 : 40'h0;
  wire [39:0] _io_rw_rdata_T_56 = io_decode_csr == 12'hb95 ? small_20 : 40'h0;
  wire [39:0] _io_rw_rdata_T_57 = io_decode_csr == 12'hb16 ? small_21 : 40'h0;
  wire [39:0] _io_rw_rdata_T_58 = io_decode_csr == 12'hb96 ? small_21 : 40'h0;
  wire [39:0] _io_rw_rdata_T_59 = io_decode_csr == 12'hb17 ? small_22 : 40'h0;
  wire [39:0] _io_rw_rdata_T_60 = io_decode_csr == 12'hb97 ? small_22 : 40'h0;
  wire [39:0] _io_rw_rdata_T_61 = io_decode_csr == 12'hb18 ? small_23 : 40'h0;
  wire [39:0] _io_rw_rdata_T_62 = io_decode_csr == 12'hb98 ? small_23 : 40'h0;
  wire [39:0] _io_rw_rdata_T_63 = io_decode_csr == 12'hb19 ? small_24 : 40'h0;
  wire [39:0] _io_rw_rdata_T_64 = io_decode_csr == 12'hb99 ? small_24 : 40'h0;
  wire [39:0] _io_rw_rdata_T_65 = io_decode_csr == 12'hb1a ? small_25 : 40'h0;
  wire [39:0] _io_rw_rdata_T_66 = io_decode_csr == 12'hb9a ? small_25 : 40'h0;
  wire [39:0] _io_rw_rdata_T_67 = io_decode_csr == 12'hb1b ? small_26 : 40'h0;
  wire [39:0] _io_rw_rdata_T_68 = io_decode_csr == 12'hb9b ? small_26 : 40'h0;
  wire [39:0] _io_rw_rdata_T_69 = io_decode_csr == 12'hb1c ? small_27 : 40'h0;
  wire [39:0] _io_rw_rdata_T_70 = io_decode_csr == 12'hb9c ? small_27 : 40'h0;
  wire [39:0] _io_rw_rdata_T_71 = io_decode_csr == 12'hb1d ? small_28 : 40'h0;
  wire [39:0] _io_rw_rdata_T_72 = io_decode_csr == 12'hb9d ? small_28 : 40'h0;
  wire [39:0] _io_rw_rdata_T_73 = io_decode_csr == 12'hb1e ? small_29 : 40'h0;
  wire [39:0] _io_rw_rdata_T_74 = io_decode_csr == 12'hb9e ? small_29 : 40'h0;
  wire [39:0] _io_rw_rdata_T_75 = io_decode_csr == 12'hb1f ? small_30 : 40'h0;
  wire [39:0] _io_rw_rdata_T_76 = io_decode_csr == 12'hb9f ? small_30 : 40'h0;
  wire [39:0] _io_rw_rdata_T_77 = io_decode_csr == 12'hb20 ? small_31 : 40'h0;
  wire [39:0] _io_rw_rdata_T_78 = io_decode_csr == 12'hba0 ? small_31 : 40'h0;
  wire [39:0] _io_rw_rdata_T_79 = io_decode_csr == 12'hb21 ? small_32 : 40'h0;
  wire [39:0] _io_rw_rdata_T_80 = io_decode_csr == 12'hba1 ? small_32 : 40'h0;
  wire [39:0] _io_rw_rdata_T_81 = io_decode_csr == 12'hb22 ? small_33 : 40'h0;
  wire [39:0] _io_rw_rdata_T_82 = io_decode_csr == 12'hba2 ? small_33 : 40'h0;
  wire [63:0] _io_rw_rdata_T_85 = _io_rw_rdata_T | _io_rw_rdata_T_1;
  wire [63:0] _GEN_151 = {{48'd0}, _io_rw_rdata_T_2};
  wire [63:0] _io_rw_rdata_T_86 = _io_rw_rdata_T_85 | _GEN_151;
  wire [63:0] _GEN_152 = {{55'd0}, _io_rw_rdata_T_5};
  wire [63:0] _io_rw_rdata_T_89 = _io_rw_rdata_T_86 | _GEN_152;
  wire [63:0] _GEN_153 = {{29'd0}, _io_rw_rdata_T_6};
  wire [63:0] _io_rw_rdata_T_90 = _io_rw_rdata_T_89 | _GEN_153;
  wire [63:0] _GEN_154 = {{55'd0}, _io_rw_rdata_T_7};
  wire [63:0] _io_rw_rdata_T_91 = _io_rw_rdata_T_90 | _GEN_154;
  wire [63:0] _GEN_155 = {{48'd0}, _io_rw_rdata_T_8};
  wire [63:0] _io_rw_rdata_T_92 = _io_rw_rdata_T_91 | _GEN_155;
  wire [63:0] _GEN_156 = {{48'd0}, _io_rw_rdata_T_9};
  wire [63:0] _io_rw_rdata_T_93 = _io_rw_rdata_T_92 | _GEN_156;
  wire [63:0] _GEN_157 = {{32'd0}, _io_rw_rdata_T_10};
  wire [63:0] _io_rw_rdata_T_94 = _io_rw_rdata_T_93 | _GEN_157;
  wire [63:0] _GEN_158 = {{32'd0}, _io_rw_rdata_T_11};
  wire [63:0] _io_rw_rdata_T_95 = _io_rw_rdata_T_94 | _GEN_158;
  wire [63:0] _GEN_159 = {{32'd0}, _io_rw_rdata_T_12};
  wire [63:0] _io_rw_rdata_T_96 = _io_rw_rdata_T_95 | _GEN_159;
  wire [63:0] _GEN_160 = {{32'd0}, _io_rw_rdata_T_13};
  wire [63:0] _io_rw_rdata_T_97 = _io_rw_rdata_T_96 | _GEN_160;
  wire [63:0] _GEN_161 = {{32'd0}, _io_rw_rdata_T_15};
  wire [63:0] _io_rw_rdata_T_99 = _io_rw_rdata_T_97 | _GEN_161;
  wire [63:0] _GEN_162 = {{32'd0}, _io_rw_rdata_T_16};
  wire [63:0] _io_rw_rdata_T_100 = _io_rw_rdata_T_99 | _GEN_162;
  wire [63:0] _GEN_163 = {{32'd0}, _io_rw_rdata_T_17};
  wire [63:0] _io_rw_rdata_T_101 = _io_rw_rdata_T_100 | _GEN_163;
  wire [63:0] _GEN_164 = {{32'd0}, _io_rw_rdata_T_18};
  wire [63:0] _io_rw_rdata_T_102 = _io_rw_rdata_T_101 | _GEN_164;
  wire [63:0] _GEN_165 = {{24'd0}, _io_rw_rdata_T_19};
  wire [63:0] _io_rw_rdata_T_103 = _io_rw_rdata_T_102 | _GEN_165;
  wire [63:0] _GEN_166 = {{24'd0}, _io_rw_rdata_T_20};
  wire [63:0] _io_rw_rdata_T_104 = _io_rw_rdata_T_103 | _GEN_166;
  wire [63:0] _GEN_167 = {{24'd0}, _io_rw_rdata_T_21};
  wire [63:0] _io_rw_rdata_T_105 = _io_rw_rdata_T_104 | _GEN_167;
  wire [63:0] _GEN_168 = {{24'd0}, _io_rw_rdata_T_22};
  wire [63:0] _io_rw_rdata_T_106 = _io_rw_rdata_T_105 | _GEN_168;
  wire [63:0] _GEN_169 = {{24'd0}, _io_rw_rdata_T_23};
  wire [63:0] _io_rw_rdata_T_107 = _io_rw_rdata_T_106 | _GEN_169;
  wire [63:0] _GEN_170 = {{24'd0}, _io_rw_rdata_T_24};
  wire [63:0] _io_rw_rdata_T_108 = _io_rw_rdata_T_107 | _GEN_170;
  wire [63:0] _GEN_171 = {{24'd0}, _io_rw_rdata_T_25};
  wire [63:0] _io_rw_rdata_T_109 = _io_rw_rdata_T_108 | _GEN_171;
  wire [63:0] _GEN_172 = {{24'd0}, _io_rw_rdata_T_26};
  wire [63:0] _io_rw_rdata_T_110 = _io_rw_rdata_T_109 | _GEN_172;
  wire [63:0] _GEN_173 = {{24'd0}, _io_rw_rdata_T_27};
  wire [63:0] _io_rw_rdata_T_111 = _io_rw_rdata_T_110 | _GEN_173;
  wire [63:0] _GEN_174 = {{24'd0}, _io_rw_rdata_T_28};
  wire [63:0] _io_rw_rdata_T_112 = _io_rw_rdata_T_111 | _GEN_174;
  wire [63:0] _GEN_175 = {{24'd0}, _io_rw_rdata_T_29};
  wire [63:0] _io_rw_rdata_T_113 = _io_rw_rdata_T_112 | _GEN_175;
  wire [63:0] _GEN_176 = {{24'd0}, _io_rw_rdata_T_30};
  wire [63:0] _io_rw_rdata_T_114 = _io_rw_rdata_T_113 | _GEN_176;
  wire [63:0] _GEN_177 = {{24'd0}, _io_rw_rdata_T_31};
  wire [63:0] _io_rw_rdata_T_115 = _io_rw_rdata_T_114 | _GEN_177;
  wire [63:0] _GEN_178 = {{24'd0}, _io_rw_rdata_T_32};
  wire [63:0] _io_rw_rdata_T_116 = _io_rw_rdata_T_115 | _GEN_178;
  wire [63:0] _GEN_179 = {{24'd0}, _io_rw_rdata_T_33};
  wire [63:0] _io_rw_rdata_T_117 = _io_rw_rdata_T_116 | _GEN_179;
  wire [63:0] _GEN_180 = {{24'd0}, _io_rw_rdata_T_34};
  wire [63:0] _io_rw_rdata_T_118 = _io_rw_rdata_T_117 | _GEN_180;
  wire [63:0] _GEN_181 = {{24'd0}, _io_rw_rdata_T_35};
  wire [63:0] _io_rw_rdata_T_119 = _io_rw_rdata_T_118 | _GEN_181;
  wire [63:0] _GEN_182 = {{24'd0}, _io_rw_rdata_T_36};
  wire [63:0] _io_rw_rdata_T_120 = _io_rw_rdata_T_119 | _GEN_182;
  wire [63:0] _GEN_183 = {{24'd0}, _io_rw_rdata_T_37};
  wire [63:0] _io_rw_rdata_T_121 = _io_rw_rdata_T_120 | _GEN_183;
  wire [63:0] _GEN_184 = {{24'd0}, _io_rw_rdata_T_38};
  wire [63:0] _io_rw_rdata_T_122 = _io_rw_rdata_T_121 | _GEN_184;
  wire [63:0] _GEN_185 = {{24'd0}, _io_rw_rdata_T_39};
  wire [63:0] _io_rw_rdata_T_123 = _io_rw_rdata_T_122 | _GEN_185;
  wire [63:0] _GEN_186 = {{24'd0}, _io_rw_rdata_T_40};
  wire [63:0] _io_rw_rdata_T_124 = _io_rw_rdata_T_123 | _GEN_186;
  wire [63:0] _GEN_187 = {{24'd0}, _io_rw_rdata_T_41};
  wire [63:0] _io_rw_rdata_T_125 = _io_rw_rdata_T_124 | _GEN_187;
  wire [63:0] _GEN_188 = {{24'd0}, _io_rw_rdata_T_42};
  wire [63:0] _io_rw_rdata_T_126 = _io_rw_rdata_T_125 | _GEN_188;
  wire [63:0] _GEN_189 = {{24'd0}, _io_rw_rdata_T_43};
  wire [63:0] _io_rw_rdata_T_127 = _io_rw_rdata_T_126 | _GEN_189;
  wire [63:0] _GEN_190 = {{24'd0}, _io_rw_rdata_T_44};
  wire [63:0] _io_rw_rdata_T_128 = _io_rw_rdata_T_127 | _GEN_190;
  wire [63:0] _GEN_191 = {{24'd0}, _io_rw_rdata_T_45};
  wire [63:0] _io_rw_rdata_T_129 = _io_rw_rdata_T_128 | _GEN_191;
  wire [63:0] _GEN_192 = {{24'd0}, _io_rw_rdata_T_46};
  wire [63:0] _io_rw_rdata_T_130 = _io_rw_rdata_T_129 | _GEN_192;
  wire [63:0] _GEN_193 = {{24'd0}, _io_rw_rdata_T_47};
  wire [63:0] _io_rw_rdata_T_131 = _io_rw_rdata_T_130 | _GEN_193;
  wire [63:0] _GEN_194 = {{24'd0}, _io_rw_rdata_T_48};
  wire [63:0] _io_rw_rdata_T_132 = _io_rw_rdata_T_131 | _GEN_194;
  wire [63:0] _GEN_195 = {{24'd0}, _io_rw_rdata_T_49};
  wire [63:0] _io_rw_rdata_T_133 = _io_rw_rdata_T_132 | _GEN_195;
  wire [63:0] _GEN_196 = {{24'd0}, _io_rw_rdata_T_50};
  wire [63:0] _io_rw_rdata_T_134 = _io_rw_rdata_T_133 | _GEN_196;
  wire [63:0] _GEN_197 = {{24'd0}, _io_rw_rdata_T_51};
  wire [63:0] _io_rw_rdata_T_135 = _io_rw_rdata_T_134 | _GEN_197;
  wire [63:0] _GEN_198 = {{24'd0}, _io_rw_rdata_T_52};
  wire [63:0] _io_rw_rdata_T_136 = _io_rw_rdata_T_135 | _GEN_198;
  wire [63:0] _GEN_199 = {{24'd0}, _io_rw_rdata_T_53};
  wire [63:0] _io_rw_rdata_T_137 = _io_rw_rdata_T_136 | _GEN_199;
  wire [63:0] _GEN_200 = {{24'd0}, _io_rw_rdata_T_54};
  wire [63:0] _io_rw_rdata_T_138 = _io_rw_rdata_T_137 | _GEN_200;
  wire [63:0] _GEN_201 = {{24'd0}, _io_rw_rdata_T_55};
  wire [63:0] _io_rw_rdata_T_139 = _io_rw_rdata_T_138 | _GEN_201;
  wire [63:0] _GEN_202 = {{24'd0}, _io_rw_rdata_T_56};
  wire [63:0] _io_rw_rdata_T_140 = _io_rw_rdata_T_139 | _GEN_202;
  wire [63:0] _GEN_203 = {{24'd0}, _io_rw_rdata_T_57};
  wire [63:0] _io_rw_rdata_T_141 = _io_rw_rdata_T_140 | _GEN_203;
  wire [63:0] _GEN_204 = {{24'd0}, _io_rw_rdata_T_58};
  wire [63:0] _io_rw_rdata_T_142 = _io_rw_rdata_T_141 | _GEN_204;
  wire [63:0] _GEN_205 = {{24'd0}, _io_rw_rdata_T_59};
  wire [63:0] _io_rw_rdata_T_143 = _io_rw_rdata_T_142 | _GEN_205;
  wire [63:0] _GEN_206 = {{24'd0}, _io_rw_rdata_T_60};
  wire [63:0] _io_rw_rdata_T_144 = _io_rw_rdata_T_143 | _GEN_206;
  wire [63:0] _GEN_207 = {{24'd0}, _io_rw_rdata_T_61};
  wire [63:0] _io_rw_rdata_T_145 = _io_rw_rdata_T_144 | _GEN_207;
  wire [63:0] _GEN_208 = {{24'd0}, _io_rw_rdata_T_62};
  wire [63:0] _io_rw_rdata_T_146 = _io_rw_rdata_T_145 | _GEN_208;
  wire [63:0] _GEN_209 = {{24'd0}, _io_rw_rdata_T_63};
  wire [63:0] _io_rw_rdata_T_147 = _io_rw_rdata_T_146 | _GEN_209;
  wire [63:0] _GEN_210 = {{24'd0}, _io_rw_rdata_T_64};
  wire [63:0] _io_rw_rdata_T_148 = _io_rw_rdata_T_147 | _GEN_210;
  wire [63:0] _GEN_211 = {{24'd0}, _io_rw_rdata_T_65};
  wire [63:0] _io_rw_rdata_T_149 = _io_rw_rdata_T_148 | _GEN_211;
  wire [63:0] _GEN_212 = {{24'd0}, _io_rw_rdata_T_66};
  wire [63:0] _io_rw_rdata_T_150 = _io_rw_rdata_T_149 | _GEN_212;
  wire [63:0] _GEN_213 = {{24'd0}, _io_rw_rdata_T_67};
  wire [63:0] _io_rw_rdata_T_151 = _io_rw_rdata_T_150 | _GEN_213;
  wire [63:0] _GEN_214 = {{24'd0}, _io_rw_rdata_T_68};
  wire [63:0] _io_rw_rdata_T_152 = _io_rw_rdata_T_151 | _GEN_214;
  wire [63:0] _GEN_215 = {{24'd0}, _io_rw_rdata_T_69};
  wire [63:0] _io_rw_rdata_T_153 = _io_rw_rdata_T_152 | _GEN_215;
  wire [63:0] _GEN_216 = {{24'd0}, _io_rw_rdata_T_70};
  wire [63:0] _io_rw_rdata_T_154 = _io_rw_rdata_T_153 | _GEN_216;
  wire [63:0] _GEN_217 = {{24'd0}, _io_rw_rdata_T_71};
  wire [63:0] _io_rw_rdata_T_155 = _io_rw_rdata_T_154 | _GEN_217;
  wire [63:0] _GEN_218 = {{24'd0}, _io_rw_rdata_T_72};
  wire [63:0] _io_rw_rdata_T_156 = _io_rw_rdata_T_155 | _GEN_218;
  wire [63:0] _GEN_219 = {{24'd0}, _io_rw_rdata_T_73};
  wire [63:0] _io_rw_rdata_T_157 = _io_rw_rdata_T_156 | _GEN_219;
  wire [63:0] _GEN_220 = {{24'd0}, _io_rw_rdata_T_74};
  wire [63:0] _io_rw_rdata_T_158 = _io_rw_rdata_T_157 | _GEN_220;
  wire [63:0] _GEN_221 = {{24'd0}, _io_rw_rdata_T_75};
  wire [63:0] _io_rw_rdata_T_159 = _io_rw_rdata_T_158 | _GEN_221;
  wire [63:0] _GEN_222 = {{24'd0}, _io_rw_rdata_T_76};
  wire [63:0] _io_rw_rdata_T_160 = _io_rw_rdata_T_159 | _GEN_222;
  wire [63:0] _GEN_223 = {{24'd0}, _io_rw_rdata_T_77};
  wire [63:0] _io_rw_rdata_T_161 = _io_rw_rdata_T_160 | _GEN_223;
  wire [63:0] _GEN_224 = {{24'd0}, _io_rw_rdata_T_78};
  wire [63:0] _io_rw_rdata_T_162 = _io_rw_rdata_T_161 | _GEN_224;
  wire [63:0] _GEN_225 = {{24'd0}, _io_rw_rdata_T_79};
  wire [63:0] _io_rw_rdata_T_163 = _io_rw_rdata_T_162 | _GEN_225;
  wire [63:0] _GEN_226 = {{24'd0}, _io_rw_rdata_T_80};
  wire [63:0] _io_rw_rdata_T_164 = _io_rw_rdata_T_163 | _GEN_226;
  wire [63:0] _GEN_227 = {{24'd0}, _io_rw_rdata_T_81};
  wire [63:0] _io_rw_rdata_T_165 = _io_rw_rdata_T_164 | _GEN_227;
  wire [63:0] _GEN_228 = {{24'd0}, _io_rw_rdata_T_82};
  wire [63:0] _io_rw_rdata_T_166 = _io_rw_rdata_T_165 | _GEN_228;
  wire [31:0] _w_T_4 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? _T_2 : 32'h0;
  wire [31:0] _w_T_5 = _w_T_4 | io_rw_wdata;
  wire [31:0] _w_T_7 = io_rw_cmd == 3'h3 ? io_rw_wdata : 32'h0;
  wire [31:0] _w_T_8 = ~_w_T_7;
  wire [31:0] w = _w_T_5 & _w_T_8;
  wire  new_dcsr_step = w[2];
  wire  new_dcsr_ebreakm = w[15];
  wire [34:0] _new_mstatus_T_3 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? read_mstatus : 35'h0;
  wire [34:0] _GEN_229 = {{3'd0}, io_rw_wdata};
  wire [34:0] _new_mstatus_T_4 = _new_mstatus_T_3 | _GEN_229;
  wire [34:0] _GEN_230 = {{3'd0}, _w_T_8};
  wire [34:0] _new_mstatus_T_8 = _new_mstatus_T_4 & _GEN_230;
  wire  new_mstatus_mie = _new_mstatus_T_8[3];
  wire  new_mstatus_mpie = _new_mstatus_T_8[7];
  wire [15:0] _new_mip_T_4 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? _T : 16'h0;
  wire [31:0] _GEN_231 = {{16'd0}, _new_mip_T_4};
  wire [31:0] _new_mip_T_5 = _GEN_231 | io_rw_wdata;
  wire [31:0] _new_mip_T_9 = _new_mip_T_5 & _w_T_8;
  wire  new_mip_msip = _new_mip_T_9[3];
  wire [15:0] _new_mie_T_4 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? _T_1 : 16'h0;
  wire [31:0] _GEN_232 = {{16'd0}, _new_mie_T_4};
  wire [31:0] _new_mie_T_5 = _GEN_232 | io_rw_wdata;
  wire [31:0] _new_mie_T_9 = _new_mie_T_5 & _w_T_8;
  wire  new_mie_msip = _new_mie_T_9[3];
  wire  new_mie_mtip = _new_mie_T_9[7];
  wire [39:0] _w_T_12 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_2 : 40'h0;
  wire [39:0] _GEN_233 = {{8'd0}, io_rw_wdata};
  wire [39:0] _w_T_13 = _w_T_12 | _GEN_233;
  wire [39:0] _GEN_234 = {{8'd0}, _w_T_8};
  wire [39:0] w_1 = _w_T_13 & _GEN_234;
  wire [39:0] _T_98 = {w_1[7:0],small_2[31:0]};
  wire [40:0] _GEN_21 = io_decode_csr == 12'hb83 ? {{1'd0}, _T_98} : nextSmall_2; // @[]
  wire [47:0] _T_100 = {small_2[39:32],w_1};
  wire [47:0] _GEN_22 = io_decode_csr == 12'hb03 ? _T_100 : {{7'd0}, _GEN_21}; // @[]
  wire [39:0] _w_T_20 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_3 : 40'h0;
  wire [39:0] _w_T_21 = _w_T_20 | _GEN_233;
  wire [39:0] w_2 = _w_T_21 & _GEN_234;
  wire [39:0] _T_103 = {w_2[7:0],small_3[31:0]};
  wire [40:0] _GEN_23 = io_decode_csr == 12'hb84 ? {{1'd0}, _T_103} : nextSmall_3; // @[]
  wire [47:0] _T_105 = {small_3[39:32],w_2};
  wire [47:0] _GEN_24 = io_decode_csr == 12'hb04 ? _T_105 : {{7'd0}, _GEN_23}; // @[]
  wire [39:0] _w_T_28 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_4 : 40'h0;
  wire [39:0] _w_T_29 = _w_T_28 | _GEN_233;
  wire [39:0] w_3 = _w_T_29 & _GEN_234;
  wire [39:0] _T_108 = {w_3[7:0],small_4[31:0]};
  wire [40:0] _GEN_25 = io_decode_csr == 12'hb85 ? {{1'd0}, _T_108} : nextSmall_4; // @[]
  wire [47:0] _T_110 = {small_4[39:32],w_3};
  wire [47:0] _GEN_26 = io_decode_csr == 12'hb05 ? _T_110 : {{7'd0}, _GEN_25}; // @[]
  wire [39:0] _w_T_36 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_5 : 40'h0;
  wire [39:0] _w_T_37 = _w_T_36 | _GEN_233;
  wire [39:0] w_4 = _w_T_37 & _GEN_234;
  wire [39:0] _T_113 = {w_4[7:0],small_5[31:0]};
  wire [40:0] _GEN_27 = io_decode_csr == 12'hb86 ? {{1'd0}, _T_113} : nextSmall_5; // @[]
  wire [47:0] _T_115 = {small_5[39:32],w_4};
  wire [47:0] _GEN_28 = io_decode_csr == 12'hb06 ? _T_115 : {{7'd0}, _GEN_27}; // @[]
  wire [39:0] _w_T_44 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_6 : 40'h0;
  wire [39:0] _w_T_45 = _w_T_44 | _GEN_233;
  wire [39:0] w_5 = _w_T_45 & _GEN_234;
  wire [39:0] _T_118 = {w_5[7:0],small_6[31:0]};
  wire [40:0] _GEN_29 = io_decode_csr == 12'hb87 ? {{1'd0}, _T_118} : nextSmall_6; // @[]
  wire [47:0] _T_120 = {small_6[39:32],w_5};
  wire [47:0] _GEN_30 = io_decode_csr == 12'hb07 ? _T_120 : {{7'd0}, _GEN_29}; // @[]
  wire [39:0] _w_T_52 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_7 : 40'h0;
  wire [39:0] _w_T_53 = _w_T_52 | _GEN_233;
  wire [39:0] w_6 = _w_T_53 & _GEN_234;
  wire [39:0] _T_123 = {w_6[7:0],small_7[31:0]};
  wire [40:0] _GEN_31 = io_decode_csr == 12'hb88 ? {{1'd0}, _T_123} : nextSmall_7; // @[]
  wire [47:0] _T_125 = {small_7[39:32],w_6};
  wire [47:0] _GEN_32 = io_decode_csr == 12'hb08 ? _T_125 : {{7'd0}, _GEN_31}; // @[]
  wire [39:0] _w_T_60 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_8 : 40'h0;
  wire [39:0] _w_T_61 = _w_T_60 | _GEN_233;
  wire [39:0] w_7 = _w_T_61 & _GEN_234;
  wire [39:0] _T_128 = {w_7[7:0],small_8[31:0]};
  wire [40:0] _GEN_33 = io_decode_csr == 12'hb89 ? {{1'd0}, _T_128} : nextSmall_8; // @[]
  wire [47:0] _T_130 = {small_8[39:32],w_7};
  wire [47:0] _GEN_34 = io_decode_csr == 12'hb09 ? _T_130 : {{7'd0}, _GEN_33}; // @[]
  wire [39:0] _w_T_68 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_9 : 40'h0;
  wire [39:0] _w_T_69 = _w_T_68 | _GEN_233;
  wire [39:0] w_8 = _w_T_69 & _GEN_234;
  wire [39:0] _T_133 = {w_8[7:0],small_9[31:0]};
  wire [40:0] _GEN_35 = io_decode_csr == 12'hb8a ? {{1'd0}, _T_133} : nextSmall_9; // @[]
  wire [47:0] _T_135 = {small_9[39:32],w_8};
  wire [47:0] _GEN_36 = io_decode_csr == 12'hb0a ? _T_135 : {{7'd0}, _GEN_35}; // @[]
  wire [39:0] _w_T_76 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_10 : 40'h0;
  wire [39:0] _w_T_77 = _w_T_76 | _GEN_233;
  wire [39:0] w_9 = _w_T_77 & _GEN_234;
  wire [39:0] _T_138 = {w_9[7:0],small_10[31:0]};
  wire [40:0] _GEN_37 = io_decode_csr == 12'hb8b ? {{1'd0}, _T_138} : nextSmall_10; // @[]
  wire [47:0] _T_140 = {small_10[39:32],w_9};
  wire [47:0] _GEN_38 = io_decode_csr == 12'hb0b ? _T_140 : {{7'd0}, _GEN_37}; // @[]
  wire [39:0] _w_T_84 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_11 : 40'h0;
  wire [39:0] _w_T_85 = _w_T_84 | _GEN_233;
  wire [39:0] w_10 = _w_T_85 & _GEN_234;
  wire [39:0] _T_143 = {w_10[7:0],small_11[31:0]};
  wire [40:0] _GEN_39 = io_decode_csr == 12'hb8c ? {{1'd0}, _T_143} : nextSmall_11; // @[]
  wire [47:0] _T_145 = {small_11[39:32],w_10};
  wire [47:0] _GEN_40 = io_decode_csr == 12'hb0c ? _T_145 : {{7'd0}, _GEN_39}; // @[]
  wire [39:0] _w_T_92 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_12 : 40'h0;
  wire [39:0] _w_T_93 = _w_T_92 | _GEN_233;
  wire [39:0] w_11 = _w_T_93 & _GEN_234;
  wire [39:0] _T_148 = {w_11[7:0],small_12[31:0]};
  wire [40:0] _GEN_41 = io_decode_csr == 12'hb8d ? {{1'd0}, _T_148} : nextSmall_12; // @[]
  wire [47:0] _T_150 = {small_12[39:32],w_11};
  wire [47:0] _GEN_42 = io_decode_csr == 12'hb0d ? _T_150 : {{7'd0}, _GEN_41}; // @[]
  wire [39:0] _w_T_100 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_13 : 40'h0;
  wire [39:0] _w_T_101 = _w_T_100 | _GEN_233;
  wire [39:0] w_12 = _w_T_101 & _GEN_234;
  wire [39:0] _T_153 = {w_12[7:0],small_13[31:0]};
  wire [40:0] _GEN_43 = io_decode_csr == 12'hb8e ? {{1'd0}, _T_153} : nextSmall_13; // @[]
  wire [47:0] _T_155 = {small_13[39:32],w_12};
  wire [47:0] _GEN_44 = io_decode_csr == 12'hb0e ? _T_155 : {{7'd0}, _GEN_43}; // @[]
  wire [39:0] _w_T_108 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_14 : 40'h0;
  wire [39:0] _w_T_109 = _w_T_108 | _GEN_233;
  wire [39:0] w_13 = _w_T_109 & _GEN_234;
  wire [39:0] _T_158 = {w_13[7:0],small_14[31:0]};
  wire [40:0] _GEN_45 = io_decode_csr == 12'hb8f ? {{1'd0}, _T_158} : nextSmall_14; // @[]
  wire [47:0] _T_160 = {small_14[39:32],w_13};
  wire [47:0] _GEN_46 = io_decode_csr == 12'hb0f ? _T_160 : {{7'd0}, _GEN_45}; // @[]
  wire [39:0] _w_T_116 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_15 : 40'h0;
  wire [39:0] _w_T_117 = _w_T_116 | _GEN_233;
  wire [39:0] w_14 = _w_T_117 & _GEN_234;
  wire [39:0] _T_163 = {w_14[7:0],small_15[31:0]};
  wire [40:0] _GEN_47 = io_decode_csr == 12'hb90 ? {{1'd0}, _T_163} : nextSmall_15; // @[]
  wire [47:0] _T_165 = {small_15[39:32],w_14};
  wire [47:0] _GEN_48 = io_decode_csr == 12'hb10 ? _T_165 : {{7'd0}, _GEN_47}; // @[]
  wire [39:0] _w_T_124 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_16 : 40'h0;
  wire [39:0] _w_T_125 = _w_T_124 | _GEN_233;
  wire [39:0] w_15 = _w_T_125 & _GEN_234;
  wire [39:0] _T_168 = {w_15[7:0],small_16[31:0]};
  wire [40:0] _GEN_49 = io_decode_csr == 12'hb91 ? {{1'd0}, _T_168} : nextSmall_16; // @[]
  wire [47:0] _T_170 = {small_16[39:32],w_15};
  wire [47:0] _GEN_50 = io_decode_csr == 12'hb11 ? _T_170 : {{7'd0}, _GEN_49}; // @[]
  wire [39:0] _w_T_132 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_17 : 40'h0;
  wire [39:0] _w_T_133 = _w_T_132 | _GEN_233;
  wire [39:0] w_16 = _w_T_133 & _GEN_234;
  wire [39:0] _T_173 = {w_16[7:0],small_17[31:0]};
  wire [40:0] _GEN_51 = io_decode_csr == 12'hb92 ? {{1'd0}, _T_173} : nextSmall_17; // @[]
  wire [47:0] _T_175 = {small_17[39:32],w_16};
  wire [47:0] _GEN_52 = io_decode_csr == 12'hb12 ? _T_175 : {{7'd0}, _GEN_51}; // @[]
  wire [39:0] _w_T_140 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_18 : 40'h0;
  wire [39:0] _w_T_141 = _w_T_140 | _GEN_233;
  wire [39:0] w_17 = _w_T_141 & _GEN_234;
  wire [39:0] _T_178 = {w_17[7:0],small_18[31:0]};
  wire [40:0] _GEN_53 = io_decode_csr == 12'hb93 ? {{1'd0}, _T_178} : nextSmall_18; // @[]
  wire [47:0] _T_180 = {small_18[39:32],w_17};
  wire [47:0] _GEN_54 = io_decode_csr == 12'hb13 ? _T_180 : {{7'd0}, _GEN_53}; // @[]
  wire [39:0] _w_T_148 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_19 : 40'h0;
  wire [39:0] _w_T_149 = _w_T_148 | _GEN_233;
  wire [39:0] w_18 = _w_T_149 & _GEN_234;
  wire [39:0] _T_183 = {w_18[7:0],small_19[31:0]};
  wire [40:0] _GEN_55 = io_decode_csr == 12'hb94 ? {{1'd0}, _T_183} : nextSmall_19; // @[]
  wire [47:0] _T_185 = {small_19[39:32],w_18};
  wire [47:0] _GEN_56 = io_decode_csr == 12'hb14 ? _T_185 : {{7'd0}, _GEN_55}; // @[]
  wire [39:0] _w_T_156 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_20 : 40'h0;
  wire [39:0] _w_T_157 = _w_T_156 | _GEN_233;
  wire [39:0] w_19 = _w_T_157 & _GEN_234;
  wire [39:0] _T_188 = {w_19[7:0],small_20[31:0]};
  wire [40:0] _GEN_57 = io_decode_csr == 12'hb95 ? {{1'd0}, _T_188} : nextSmall_20; // @[]
  wire [47:0] _T_190 = {small_20[39:32],w_19};
  wire [47:0] _GEN_58 = io_decode_csr == 12'hb15 ? _T_190 : {{7'd0}, _GEN_57}; // @[]
  wire [39:0] _w_T_164 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_21 : 40'h0;
  wire [39:0] _w_T_165 = _w_T_164 | _GEN_233;
  wire [39:0] w_20 = _w_T_165 & _GEN_234;
  wire [39:0] _T_193 = {w_20[7:0],small_21[31:0]};
  wire [40:0] _GEN_59 = io_decode_csr == 12'hb96 ? {{1'd0}, _T_193} : nextSmall_21; // @[]
  wire [47:0] _T_195 = {small_21[39:32],w_20};
  wire [47:0] _GEN_60 = io_decode_csr == 12'hb16 ? _T_195 : {{7'd0}, _GEN_59}; // @[]
  wire [39:0] _w_T_172 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_22 : 40'h0;
  wire [39:0] _w_T_173 = _w_T_172 | _GEN_233;
  wire [39:0] w_21 = _w_T_173 & _GEN_234;
  wire [39:0] _T_198 = {w_21[7:0],small_22[31:0]};
  wire [40:0] _GEN_61 = io_decode_csr == 12'hb97 ? {{1'd0}, _T_198} : nextSmall_22; // @[]
  wire [47:0] _T_200 = {small_22[39:32],w_21};
  wire [47:0] _GEN_62 = io_decode_csr == 12'hb17 ? _T_200 : {{7'd0}, _GEN_61}; // @[]
  wire [39:0] _w_T_180 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_23 : 40'h0;
  wire [39:0] _w_T_181 = _w_T_180 | _GEN_233;
  wire [39:0] w_22 = _w_T_181 & _GEN_234;
  wire [39:0] _T_203 = {w_22[7:0],small_23[31:0]};
  wire [40:0] _GEN_63 = io_decode_csr == 12'hb98 ? {{1'd0}, _T_203} : nextSmall_23; // @[]
  wire [47:0] _T_205 = {small_23[39:32],w_22};
  wire [47:0] _GEN_64 = io_decode_csr == 12'hb18 ? _T_205 : {{7'd0}, _GEN_63}; // @[]
  wire [39:0] _w_T_188 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_24 : 40'h0;
  wire [39:0] _w_T_189 = _w_T_188 | _GEN_233;
  wire [39:0] w_23 = _w_T_189 & _GEN_234;
  wire [39:0] _T_208 = {w_23[7:0],small_24[31:0]};
  wire [40:0] _GEN_65 = io_decode_csr == 12'hb99 ? {{1'd0}, _T_208} : nextSmall_24; // @[]
  wire [47:0] _T_210 = {small_24[39:32],w_23};
  wire [47:0] _GEN_66 = io_decode_csr == 12'hb19 ? _T_210 : {{7'd0}, _GEN_65}; // @[]
  wire [39:0] _w_T_196 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_25 : 40'h0;
  wire [39:0] _w_T_197 = _w_T_196 | _GEN_233;
  wire [39:0] w_24 = _w_T_197 & _GEN_234;
  wire [39:0] _T_213 = {w_24[7:0],small_25[31:0]};
  wire [40:0] _GEN_67 = io_decode_csr == 12'hb9a ? {{1'd0}, _T_213} : nextSmall_25; // @[]
  wire [47:0] _T_215 = {small_25[39:32],w_24};
  wire [47:0] _GEN_68 = io_decode_csr == 12'hb1a ? _T_215 : {{7'd0}, _GEN_67}; // @[]
  wire [39:0] _w_T_204 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_26 : 40'h0;
  wire [39:0] _w_T_205 = _w_T_204 | _GEN_233;
  wire [39:0] w_25 = _w_T_205 & _GEN_234;
  wire [39:0] _T_218 = {w_25[7:0],small_26[31:0]};
  wire [40:0] _GEN_69 = io_decode_csr == 12'hb9b ? {{1'd0}, _T_218} : nextSmall_26; // @[]
  wire [47:0] _T_220 = {small_26[39:32],w_25};
  wire [47:0] _GEN_70 = io_decode_csr == 12'hb1b ? _T_220 : {{7'd0}, _GEN_69}; // @[]
  wire [39:0] _w_T_212 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_27 : 40'h0;
  wire [39:0] _w_T_213 = _w_T_212 | _GEN_233;
  wire [39:0] w_26 = _w_T_213 & _GEN_234;
  wire [39:0] _T_223 = {w_26[7:0],small_27[31:0]};
  wire [40:0] _GEN_71 = io_decode_csr == 12'hb9c ? {{1'd0}, _T_223} : nextSmall_27; // @[]
  wire [47:0] _T_225 = {small_27[39:32],w_26};
  wire [47:0] _GEN_72 = io_decode_csr == 12'hb1c ? _T_225 : {{7'd0}, _GEN_71}; // @[]
  wire [39:0] _w_T_220 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_28 : 40'h0;
  wire [39:0] _w_T_221 = _w_T_220 | _GEN_233;
  wire [39:0] w_27 = _w_T_221 & _GEN_234;
  wire [39:0] _T_228 = {w_27[7:0],small_28[31:0]};
  wire [40:0] _GEN_73 = io_decode_csr == 12'hb9d ? {{1'd0}, _T_228} : nextSmall_28; // @[]
  wire [47:0] _T_230 = {small_28[39:32],w_27};
  wire [47:0] _GEN_74 = io_decode_csr == 12'hb1d ? _T_230 : {{7'd0}, _GEN_73}; // @[]
  wire [39:0] _w_T_228 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_29 : 40'h0;
  wire [39:0] _w_T_229 = _w_T_228 | _GEN_233;
  wire [39:0] w_28 = _w_T_229 & _GEN_234;
  wire [39:0] _T_233 = {w_28[7:0],small_29[31:0]};
  wire [40:0] _GEN_75 = io_decode_csr == 12'hb9e ? {{1'd0}, _T_233} : nextSmall_29; // @[]
  wire [47:0] _T_235 = {small_29[39:32],w_28};
  wire [47:0] _GEN_76 = io_decode_csr == 12'hb1e ? _T_235 : {{7'd0}, _GEN_75}; // @[]
  wire [39:0] _w_T_236 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_30 : 40'h0;
  wire [39:0] _w_T_237 = _w_T_236 | _GEN_233;
  wire [39:0] w_29 = _w_T_237 & _GEN_234;
  wire [39:0] _T_238 = {w_29[7:0],small_30[31:0]};
  wire [40:0] _GEN_77 = io_decode_csr == 12'hb9f ? {{1'd0}, _T_238} : nextSmall_30; // @[]
  wire [47:0] _T_240 = {small_30[39:32],w_29};
  wire [47:0] _GEN_78 = io_decode_csr == 12'hb1f ? _T_240 : {{7'd0}, _GEN_77}; // @[]
  wire [39:0] _w_T_244 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_31 : 40'h0;
  wire [39:0] _w_T_245 = _w_T_244 | _GEN_233;
  wire [39:0] w_30 = _w_T_245 & _GEN_234;
  wire [39:0] _T_243 = {w_30[7:0],small_31[31:0]};
  wire [40:0] _GEN_79 = io_decode_csr == 12'hba0 ? {{1'd0}, _T_243} : nextSmall_31; // @[]
  wire [47:0] _T_245 = {small_31[39:32],w_30};
  wire [47:0] _GEN_80 = io_decode_csr == 12'hb20 ? _T_245 : {{7'd0}, _GEN_79}; // @[]
  wire [39:0] _w_T_252 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_32 : 40'h0;
  wire [39:0] _w_T_253 = _w_T_252 | _GEN_233;
  wire [39:0] w_31 = _w_T_253 & _GEN_234;
  wire [39:0] _T_248 = {w_31[7:0],small_32[31:0]};
  wire [40:0] _GEN_81 = io_decode_csr == 12'hba1 ? {{1'd0}, _T_248} : nextSmall_32; // @[]
  wire [47:0] _T_250 = {small_32[39:32],w_31};
  wire [47:0] _GEN_82 = io_decode_csr == 12'hb21 ? _T_250 : {{7'd0}, _GEN_81}; // @[]
  wire [39:0] _w_T_260 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? small_33 : 40'h0;
  wire [39:0] _w_T_261 = _w_T_260 | _GEN_233;
  wire [39:0] w_32 = _w_T_261 & _GEN_234;
  wire [39:0] _T_253 = {w_32[7:0],small_33[31:0]};
  wire [40:0] _GEN_83 = io_decode_csr == 12'hba2 ? {{1'd0}, _T_253} : nextSmall_33; // @[]
  wire [47:0] _T_255 = {small_33[39:32],w_32};
  wire [47:0] _GEN_84 = io_decode_csr == 12'hb22 ? _T_255 : {{7'd0}, _GEN_83}; // @[]
  wire [63:0] _w_T_268 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? value : 64'h0;
  wire [63:0] _GEN_297 = {{32'd0}, io_rw_wdata};
  wire [63:0] _w_T_269 = _w_T_268 | _GEN_297;
  wire [63:0] _GEN_298 = {{32'd0}, _w_T_8};
  wire [63:0] w_33 = _w_T_269 & _GEN_298;
  wire [63:0] _T_258 = {w_33[31:0],value[31:0]};
  wire [63:0] _GEN_85 = io_decode_csr == 12'hb80 ? _T_258 : {{57'd0}, nextSmall}; // @[]
  wire [57:0] _GEN_86 = io_decode_csr == 12'hb80 ? _T_258[63:6] : _GEN_0; // @[]
  wire [95:0] _T_260 = {value[63:32],w_33};
  wire [95:0] _GEN_87 = io_decode_csr == 12'hb00 ? _T_260 : {{32'd0}, _GEN_85}; // @[]
  wire [89:0] _GEN_88 = io_decode_csr == 12'hb00 ? _T_260[95:6] : {{32'd0}, _GEN_86}; // @[]
  wire [63:0] _w_T_276 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? value_1 : 64'h0;
  wire [63:0] _w_T_277 = _w_T_276 | _GEN_297;
  wire [63:0] w_34 = _w_T_277 & _GEN_298;
  wire [63:0] _T_263 = {w_34[31:0],value_1[31:0]};
  wire [63:0] _GEN_89 = io_decode_csr == 12'hb82 ? _T_263 : {{57'd0}, nextSmall_1}; // @[]
  wire [57:0] _GEN_90 = io_decode_csr == 12'hb82 ? _T_263[63:6] : _GEN_1; // @[]
  wire [95:0] _T_265 = {value_1[63:32],w_34};
  wire [95:0] _GEN_91 = io_decode_csr == 12'hb02 ? _T_265 : {{32'd0}, _GEN_89}; // @[]
  wire [89:0] _GEN_92 = io_decode_csr == 12'hb02 ? _T_265[95:6] : {{32'd0}, _GEN_90}; // @[]
  wire [31:0] _reg_dpc_T_3 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_dpc : 32'h0;
  wire [31:0] _reg_dpc_T_4 = _reg_dpc_T_3 | io_rw_wdata;
  wire [31:0] _reg_dpc_T_8 = _reg_dpc_T_4 & _w_T_8;
  wire [31:0] _reg_dscratch_T_3 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_dscratch : 32'h0;
  wire [31:0] _reg_dscratch_T_4 = _reg_dscratch_T_3 | io_rw_wdata;
  wire [31:0] _reg_dscratch_T_8 = _reg_dscratch_T_4 & _w_T_8;
  wire [31:0] _w_T_284 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_mepc : 32'h0;
  wire [31:0] _w_T_285 = _w_T_284 | io_rw_wdata;
  wire [31:0] w_35 = _w_T_285 & _w_T_8;
  wire [31:0] _reg_mepc_T_1 = {{2'd0}, w_35[31:2]};
  wire [33:0] _GEN_302 = {_reg_mepc_T_1, 2'h0};
  wire [34:0] _reg_mepc_T_2 = {{1'd0}, _GEN_302};
  wire [34:0] _GEN_95 = io_decode_csr == 12'h341 ? _reg_mepc_T_2 : {{3'd0}, _GEN_13}; // @[]
  wire [31:0] _reg_mscratch_T_3 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_mscratch : 32'h0;
  wire [31:0] _reg_mscratch_T_4 = _reg_mscratch_T_3 | io_rw_wdata;
  wire [31:0] _reg_mscratch_T_8 = _reg_mscratch_T_4 & _w_T_8;
  wire [31:0] _reg_mcause_T_5 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_mcause : 32'h0;
  wire [31:0] _reg_mcause_T_6 = _reg_mcause_T_5 | io_rw_wdata;
  wire [31:0] _reg_mcause_T_10 = _reg_mcause_T_6 & _w_T_8;
  wire [31:0] _reg_mcause_T_11 = _reg_mcause_T_10 & 32'h8000001f;
  wire [31:0] _w_T_292 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_mtval : 32'h0;
  wire [31:0] _w_T_293 = _w_T_292 | io_rw_wdata;
  wire [31:0] w_36 = _w_T_293 & _w_T_8;
  wire [31:0] _w_T_300 = io_rw_cmd == 3'h2 | io_rw_cmd == 3'h3 ? reg_medeleg : 32'h0;
  wire [31:0] _w_T_301 = _w_T_300 | io_rw_wdata;
  wire [31:0] w_37 = _w_T_301 & _w_T_8;
  wire [47:0] _GEN_107 = wen ? _GEN_22 : {{7'd0}, nextSmall_2}; // @[]
  wire [47:0] _GEN_108 = wen ? _GEN_24 : {{7'd0}, nextSmall_3}; // @[]
  wire [47:0] _GEN_109 = wen ? _GEN_26 : {{7'd0}, nextSmall_4}; // @[]
  wire [47:0] _GEN_110 = wen ? _GEN_28 : {{7'd0}, nextSmall_5}; // @[]
  wire [47:0] _GEN_111 = wen ? _GEN_30 : {{7'd0}, nextSmall_6}; // @[]
  wire [47:0] _GEN_112 = wen ? _GEN_32 : {{7'd0}, nextSmall_7}; // @[]
  wire [47:0] _GEN_113 = wen ? _GEN_34 : {{7'd0}, nextSmall_8}; // @[]
  wire [47:0] _GEN_114 = wen ? _GEN_36 : {{7'd0}, nextSmall_9}; // @[]
  wire [47:0] _GEN_115 = wen ? _GEN_38 : {{7'd0}, nextSmall_10}; // @[]
  wire [47:0] _GEN_116 = wen ? _GEN_40 : {{7'd0}, nextSmall_11}; // @[]
  wire [47:0] _GEN_117 = wen ? _GEN_42 : {{7'd0}, nextSmall_12}; // @[]
  wire [47:0] _GEN_118 = wen ? _GEN_44 : {{7'd0}, nextSmall_13}; // @[]
  wire [47:0] _GEN_119 = wen ? _GEN_46 : {{7'd0}, nextSmall_14}; // @[]
  wire [47:0] _GEN_120 = wen ? _GEN_48 : {{7'd0}, nextSmall_15}; // @[]
  wire [47:0] _GEN_121 = wen ? _GEN_50 : {{7'd0}, nextSmall_16}; // @[]
  wire [47:0] _GEN_122 = wen ? _GEN_52 : {{7'd0}, nextSmall_17}; // @[]
  wire [47:0] _GEN_123 = wen ? _GEN_54 : {{7'd0}, nextSmall_18}; // @[]
  wire [47:0] _GEN_124 = wen ? _GEN_56 : {{7'd0}, nextSmall_19}; // @[]
  wire [47:0] _GEN_125 = wen ? _GEN_58 : {{7'd0}, nextSmall_20}; // @[]
  wire [47:0] _GEN_126 = wen ? _GEN_60 : {{7'd0}, nextSmall_21}; // @[]
  wire [47:0] _GEN_127 = wen ? _GEN_62 : {{7'd0}, nextSmall_22}; // @[]
  wire [47:0] _GEN_128 = wen ? _GEN_64 : {{7'd0}, nextSmall_23}; // @[]
  wire [47:0] _GEN_129 = wen ? _GEN_66 : {{7'd0}, nextSmall_24}; // @[]
  wire [47:0] _GEN_130 = wen ? _GEN_68 : {{7'd0}, nextSmall_25}; // @[]
  wire [47:0] _GEN_131 = wen ? _GEN_70 : {{7'd0}, nextSmall_26}; // @[]
  wire [47:0] _GEN_132 = wen ? _GEN_72 : {{7'd0}, nextSmall_27}; // @[]
  wire [47:0] _GEN_133 = wen ? _GEN_74 : {{7'd0}, nextSmall_28}; // @[]
  wire [47:0] _GEN_134 = wen ? _GEN_76 : {{7'd0}, nextSmall_29}; // @[]
  wire [47:0] _GEN_135 = wen ? _GEN_78 : {{7'd0}, nextSmall_30}; // @[]
  wire [47:0] _GEN_136 = wen ? _GEN_80 : {{7'd0}, nextSmall_31}; // @[]
  wire [47:0] _GEN_137 = wen ? _GEN_82 : {{7'd0}, nextSmall_32}; // @[]
  wire [47:0] _GEN_138 = wen ? _GEN_84 : {{7'd0}, nextSmall_33}; // @[]
  wire [95:0] _GEN_139 = wen ? _GEN_87 : {{89'd0}, nextSmall}; // @[]
  wire [89:0] _GEN_140 = wen ? _GEN_88 : {{32'd0}, _GEN_0}; // @[]
  wire [95:0] _GEN_141 = wen ? _GEN_91 : {{89'd0}, nextSmall_1}; // @[]
  wire [89:0] _GEN_142 = wen ? _GEN_92 : {{32'd0}, _GEN_1}; // @[]
  wire [34:0] _GEN_145 = wen ? _GEN_95 : {{3'd0}, _GEN_13}; // @[]
  wire [95:0] _GEN_303 = reset ? 96'h0 : _GEN_139;
  wire [89:0] _GEN_304 = reset ? 90'h0 : _GEN_140;
  wire [95:0] _GEN_305 = reset ? 96'h0 : _GEN_141;
  wire [89:0] _GEN_306 = reset ? 90'h0 : _GEN_142;
  assign io_rw_rdata = _io_rw_rdata_T_166[31:0];
  assign io_eret = insn_call | insn_break | insn_ret;
  assign io_status_debug = 1'h0;
  assign io_status_prv = 2'h3;
  assign io_status_sd = 1'h0;
  assign io_status_zero1 = 8'h0;
  assign io_status_tsr = 1'h0;
  assign io_status_tw = 1'h0;
  assign io_status_tvm = 1'h0;
  assign io_status_mxr = 1'h0;
  assign io_status_sum = 1'h0;
  assign io_status_mprv = 1'h0;
  assign io_status_xs = 2'h0;
  assign io_status_fs = 2'h0;
  assign io_status_mpp = 2'h3;
  assign io_status_hpp = 2'h0;
  assign io_status_spp = 1'h0;
  assign io_status_mpie = reg_mstatus_mpie;
  assign io_status_hpie = 1'h0;
  assign io_status_spie = 1'h0;
  assign io_status_upie = 1'h0;
  assign io_status_mie = reg_mstatus_mie;
  assign io_status_hie = 1'h0;
  assign io_status_sie = 1'h0;
  assign io_status_uie = 1'h0;
  assign io_evec = insn_ret & ~io_decode_csr[10] ? reg_mepc : _GEN_6; // @[]
  always @(posedge clock) begin
    if (reset) begin
      reg_mstatus_mpie <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h300) begin
        reg_mstatus_mpie <= new_mstatus_mpie;
      end else begin
        reg_mstatus_mpie <= insn_ret & ~io_decode_csr[10] | reg_mstatus_mpie;
      end
    end else begin
      reg_mstatus_mpie <= insn_ret & ~io_decode_csr[10] | reg_mstatus_mpie;
    end
    if (reset) begin
      reg_mstatus_mie <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h300) begin
        reg_mstatus_mie <= new_mstatus_mie;
      end else begin
        reg_mstatus_mie <= _GEN_7;
      end
    end else begin
      reg_mstatus_mie <= _GEN_7;
    end
    reg_mepc <= _GEN_145[31:0];
    if (wen) begin
      if (io_decode_csr == 12'h342) begin
        reg_mcause <= _reg_mcause_T_11;
      end else begin
        reg_mcause <= _GEN_12;
      end
    end else begin
      reg_mcause <= _GEN_12;
    end
    if (wen) begin
      if (io_decode_csr == 12'h343) begin
        reg_mtval <= w_36;
      end
    end
    if (wen) begin
      if (io_decode_csr == 12'h340) begin
        reg_mscratch <= _reg_mscratch_T_8;
      end
    end
    if (wen) begin
      if (io_decode_csr == 12'h302) begin
        reg_medeleg <= w_37;
      end
    end
    if (reset) begin
      reg_mip_mtip <= 1'h0;
    end else begin
      reg_mip_mtip <= 1'h1;
    end
    if (reset) begin
      reg_mip_msip <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h344) begin
        reg_mip_msip <= new_mip_msip;
      end
    end
    if (reset) begin
      reg_mie_mtip <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h304) begin
        reg_mie_mtip <= new_mie_mtip;
      end
    end
    if (reset) begin
      reg_mie_msip <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h304) begin
        reg_mie_msip <= new_mie_msip;
      end
    end
    small_ <= _GEN_303[5:0];
    large_ <= _GEN_304[57:0];
    small_1 <= _GEN_305[5:0];
    large_1 <= _GEN_306[57:0];
    small_2 <= _GEN_107[39:0];
    small_3 <= _GEN_108[39:0];
    small_4 <= _GEN_109[39:0];
    small_5 <= _GEN_110[39:0];
    small_6 <= _GEN_111[39:0];
    small_7 <= _GEN_112[39:0];
    small_8 <= _GEN_113[39:0];
    small_9 <= _GEN_114[39:0];
    small_10 <= _GEN_115[39:0];
    small_11 <= _GEN_116[39:0];
    small_12 <= _GEN_117[39:0];
    small_13 <= _GEN_118[39:0];
    small_14 <= _GEN_119[39:0];
    small_15 <= _GEN_120[39:0];
    small_16 <= _GEN_121[39:0];
    small_17 <= _GEN_122[39:0];
    small_18 <= _GEN_123[39:0];
    small_19 <= _GEN_124[39:0];
    small_20 <= _GEN_125[39:0];
    small_21 <= _GEN_126[39:0];
    small_22 <= _GEN_127[39:0];
    small_23 <= _GEN_128[39:0];
    small_24 <= _GEN_129[39:0];
    small_25 <= _GEN_130[39:0];
    small_26 <= _GEN_131[39:0];
    small_27 <= _GEN_132[39:0];
    small_28 <= _GEN_133[39:0];
    small_29 <= _GEN_134[39:0];
    small_30 <= _GEN_135[39:0];
    small_31 <= _GEN_136[39:0];
    small_32 <= _GEN_137[39:0];
    small_33 <= _GEN_138[39:0];
    if (wen) begin
      if (io_decode_csr == 12'h7b1) begin
        reg_dpc <= _reg_dpc_T_8;
      end
    end
    if (wen) begin
      if (io_decode_csr == 12'h7b2) begin
        reg_dscratch <= _reg_dscratch_T_8;
      end
    end
    if (reset) begin
      reg_dcsr_ebreakm <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h7b0) begin
        reg_dcsr_ebreakm <= new_dcsr_ebreakm;
      end
    end
    if (reset) begin
      reg_dcsr_step <= 1'h0;
    end else if (wen) begin
      if (io_decode_csr == 12'h7b0) begin
        reg_dcsr_step <= new_dcsr_step;
      end
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  reg_mstatus_mpie = _RAND_0[0:0];
  _RAND_1 = {1{`RANDOM}};
  reg_mstatus_mie = _RAND_1[0:0];
  _RAND_2 = {1{`RANDOM}};
  reg_mepc = _RAND_2[31:0];
  _RAND_3 = {1{`RANDOM}};
  reg_mcause = _RAND_3[31:0];
  _RAND_4 = {1{`RANDOM}};
  reg_mtval = _RAND_4[31:0];
  _RAND_5 = {1{`RANDOM}};
  reg_mscratch = _RAND_5[31:0];
  _RAND_6 = {1{`RANDOM}};
  reg_medeleg = _RAND_6[31:0];
  _RAND_7 = {1{`RANDOM}};
  reg_mip_mtip = _RAND_7[0:0];
  _RAND_8 = {1{`RANDOM}};
  reg_mip_msip = _RAND_8[0:0];
  _RAND_9 = {1{`RANDOM}};
  reg_mie_mtip = _RAND_9[0:0];
  _RAND_10 = {1{`RANDOM}};
  reg_mie_msip = _RAND_10[0:0];
  _RAND_11 = {1{`RANDOM}};
  small_ = _RAND_11[5:0];
  _RAND_12 = {2{`RANDOM}};
  large_ = _RAND_12[57:0];
  _RAND_13 = {1{`RANDOM}};
  small_1 = _RAND_13[5:0];
  _RAND_14 = {2{`RANDOM}};
  large_1 = _RAND_14[57:0];
  _RAND_15 = {2{`RANDOM}};
  small_2 = _RAND_15[39:0];
  _RAND_16 = {2{`RANDOM}};
  small_3 = _RAND_16[39:0];
  _RAND_17 = {2{`RANDOM}};
  small_4 = _RAND_17[39:0];
  _RAND_18 = {2{`RANDOM}};
  small_5 = _RAND_18[39:0];
  _RAND_19 = {2{`RANDOM}};
  small_6 = _RAND_19[39:0];
  _RAND_20 = {2{`RANDOM}};
  small_7 = _RAND_20[39:0];
  _RAND_21 = {2{`RANDOM}};
  small_8 = _RAND_21[39:0];
  _RAND_22 = {2{`RANDOM}};
  small_9 = _RAND_22[39:0];
  _RAND_23 = {2{`RANDOM}};
  small_10 = _RAND_23[39:0];
  _RAND_24 = {2{`RANDOM}};
  small_11 = _RAND_24[39:0];
  _RAND_25 = {2{`RANDOM}};
  small_12 = _RAND_25[39:0];
  _RAND_26 = {2{`RANDOM}};
  small_13 = _RAND_26[39:0];
  _RAND_27 = {2{`RANDOM}};
  small_14 = _RAND_27[39:0];
  _RAND_28 = {2{`RANDOM}};
  small_15 = _RAND_28[39:0];
  _RAND_29 = {2{`RANDOM}};
  small_16 = _RAND_29[39:0];
  _RAND_30 = {2{`RANDOM}};
  small_17 = _RAND_30[39:0];
  _RAND_31 = {2{`RANDOM}};
  small_18 = _RAND_31[39:0];
  _RAND_32 = {2{`RANDOM}};
  small_19 = _RAND_32[39:0];
  _RAND_33 = {2{`RANDOM}};
  small_20 = _RAND_33[39:0];
  _RAND_34 = {2{`RANDOM}};
  small_21 = _RAND_34[39:0];
  _RAND_35 = {2{`RANDOM}};
  small_22 = _RAND_35[39:0];
  _RAND_36 = {2{`RANDOM}};
  small_23 = _RAND_36[39:0];
  _RAND_37 = {2{`RANDOM}};
  small_24 = _RAND_37[39:0];
  _RAND_38 = {2{`RANDOM}};
  small_25 = _RAND_38[39:0];
  _RAND_39 = {2{`RANDOM}};
  small_26 = _RAND_39[39:0];
  _RAND_40 = {2{`RANDOM}};
  small_27 = _RAND_40[39:0];
  _RAND_41 = {2{`RANDOM}};
  small_28 = _RAND_41[39:0];
  _RAND_42 = {2{`RANDOM}};
  small_29 = _RAND_42[39:0];
  _RAND_43 = {2{`RANDOM}};
  small_30 = _RAND_43[39:0];
  _RAND_44 = {2{`RANDOM}};
  small_31 = _RAND_44[39:0];
  _RAND_45 = {2{`RANDOM}};
  small_32 = _RAND_45[39:0];
  _RAND_46 = {2{`RANDOM}};
  small_33 = _RAND_46[39:0];
  _RAND_47 = {1{`RANDOM}};
  reg_dpc = _RAND_47[31:0];
  _RAND_48 = {1{`RANDOM}};
  reg_dscratch = _RAND_48[31:0];
  _RAND_49 = {1{`RANDOM}};
  reg_dcsr_ebreakm = _RAND_49[0:0];
  _RAND_50 = {1{`RANDOM}};
  reg_dcsr_step = _RAND_50[0:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module DatPath(
  input         clock,
  input         reset,
  output [31:0] io_imem_req_bits_addr,
  input  [31:0] io_imem_resp_bits_data,
  output        io_dmem_req_valid,
  output [31:0] io_dmem_req_bits_addr,
  output [31:0] io_dmem_req_bits_data,
  output        io_dmem_req_bits_fcn,
  output [2:0]  io_dmem_req_bits_typ,
  input  [31:0] io_dmem_resp_bits_data,
  input         io_ctl_dec_stall,
  input         io_ctl_full_stall,
  input  [1:0]  io_ctl_exe_pc_sel,
  input  [3:0]  io_ctl_br_type,
  input         io_ctl_if_kill,
  input         io_ctl_dec_kill,
  input  [1:0]  io_ctl_op1_sel,
  input  [2:0]  io_ctl_op2_sel,
  input  [3:0]  io_ctl_alu_fun,
  input  [1:0]  io_ctl_wb_sel,
  input         io_ctl_rf_wen,
  input         io_ctl_mem_val,
  input  [1:0]  io_ctl_mem_fcn,
  input  [2:0]  io_ctl_mem_typ,
  input  [2:0]  io_ctl_csr_cmd,
  input         io_ctl_fencei,
  input         io_ctl_pipeline_kill,
  input         io_ctl_mem_exception,
  output [31:0] io_dat_dec_inst,
  output        io_dat_exe_br_eq,
  output        io_dat_exe_br_lt,
  output        io_dat_exe_br_ltu,
  output [3:0]  io_dat_exe_br_type,
  output        io_dat_mem_ctrl_dmem_val,
  output        io_dat_csr_eret,
  output [4:0]  io_rf_read_rs1_addr,
  input  [31:0] io_rf_read_rs1_data,
  output [4:0]  io_rf_read_rs2_addr,
  input  [31:0] io_rf_read_rs2_data,
  output [4:0]  io_rf_write_waddr,
  output [31:0] io_rf_write_wdata,
  output        io_rf_write_wen
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
  reg [31:0] _RAND_2;
  reg [31:0] _RAND_3;
  reg [31:0] _RAND_4;
  reg [31:0] _RAND_5;
  reg [31:0] _RAND_6;
  reg [31:0] _RAND_7;
  reg [31:0] _RAND_8;
  reg [31:0] _RAND_9;
  reg [31:0] _RAND_10;
  reg [31:0] _RAND_11;
  reg [31:0] _RAND_12;
  reg [31:0] _RAND_13;
  reg [31:0] _RAND_14;
  reg [31:0] _RAND_15;
  reg [31:0] _RAND_16;
  reg [31:0] _RAND_17;
  reg [31:0] _RAND_18;
  reg [31:0] _RAND_19;
  reg [31:0] _RAND_20;
  reg [31:0] _RAND_21;
  reg [31:0] _RAND_22;
  reg [31:0] _RAND_23;
  reg [31:0] _RAND_24;
  reg [31:0] _RAND_25;
  reg [31:0] _RAND_26;
  reg [31:0] _RAND_27;
  reg [31:0] _RAND_28;
  reg [31:0] _RAND_29;
  reg [31:0] _RAND_30;
  reg [31:0] _RAND_31;
  reg [31:0] _RAND_32;
  reg [31:0] _RAND_33;
  reg [31:0] _RAND_34;
`endif // RANDOMIZE_REG_INIT
  wire  csr_clock;
  wire  csr_reset;
  wire [2:0] csr_io_rw_cmd;
  wire [31:0] csr_io_rw_rdata;
  wire [31:0] csr_io_rw_wdata;
  wire  csr_io_eret;
  wire [11:0] csr_io_decode_csr;
  wire  csr_io_status_debug;
  wire [1:0] csr_io_status_prv;
  wire  csr_io_status_sd;
  wire [7:0] csr_io_status_zero1;
  wire  csr_io_status_tsr;
  wire  csr_io_status_tw;
  wire  csr_io_status_tvm;
  wire  csr_io_status_mxr;
  wire  csr_io_status_sum;
  wire  csr_io_status_mprv;
  wire [1:0] csr_io_status_xs;
  wire [1:0] csr_io_status_fs;
  wire [1:0] csr_io_status_mpp;
  wire [1:0] csr_io_status_hpp;
  wire  csr_io_status_spp;
  wire  csr_io_status_mpie;
  wire  csr_io_status_hpie;
  wire  csr_io_status_spie;
  wire  csr_io_status_upie;
  wire  csr_io_status_mie;
  wire  csr_io_status_hie;
  wire  csr_io_status_sie;
  wire  csr_io_status_uie;
  wire [31:0] csr_io_evec;
  wire  csr_io_exception;
  wire  csr_io_retire;
  wire [31:0] csr_io_pc;
  reg [31:0] if_reg_pc;
  reg  dec_reg_valid;
  reg [31:0] dec_reg_inst;
  reg [31:0] dec_reg_pc;
  reg  exe_reg_valid;
  reg [31:0] exe_reg_inst;
  reg [31:0] exe_reg_pc;
  reg [4:0] exe_reg_wbaddr;
  reg [31:0] exe_alu_op1;
  reg [31:0] brjmp_offset;
  reg [31:0] exe_reg_rs2_data;
  reg [3:0] exe_reg_ctrl_br_type;
  reg [3:0] exe_reg_ctrl_alu_fun;
  reg [1:0] exe_reg_ctrl_wb_sel;
  reg  exe_reg_ctrl_rf_wen;
  reg  exe_reg_ctrl_mem_val;
  reg  exe_reg_ctrl_mem_fcn;
  reg [2:0] exe_reg_ctrl_mem_typ;
  reg [2:0] exe_reg_ctrl_csr_cmd;
  reg  mem_reg_valid;
  reg [31:0] mem_reg_pc;
  reg [31:0] mem_reg_inst;
  reg [31:0] mem_reg_alu_out;
  reg [4:0] mem_reg_wbaddr;
  reg [31:0] mem_reg_rs2_data;
  reg  mem_reg_ctrl_rf_wen;
  reg  mem_reg_ctrl_mem_val;
  reg  mem_reg_ctrl_mem_fcn;
  reg [2:0] mem_reg_ctrl_mem_typ;
  reg [1:0] mem_reg_ctrl_wb_sel;
  reg [2:0] mem_reg_ctrl_csr_cmd;
  reg  wb_reg_valid;
  reg [4:0] wb_reg_wbaddr;
  reg [31:0] wb_reg_wbdata;
  reg  wb_reg_ctrl_rf_wen;
  wire [31:0] if_pc_plus4 = if_reg_pc + 32'h4;
  wire [31:0] exe_brjmp_target = exe_reg_pc + brjmp_offset;
  wire [31:0] exe_adder_out = exe_alu_op1 + brjmp_offset;
  wire [31:0] exception_target = csr_io_evec;
  wire [31:0] _if_pc_next_T_3 = io_ctl_exe_pc_sel == 2'h2 ? exe_adder_out : exception_target;
  wire [31:0] _if_pc_next_T_4 = io_ctl_exe_pc_sel == 2'h1 ? exe_brjmp_target : _if_pc_next_T_3;
  wire [4:0] dec_rs1_addr = dec_reg_inst[19:15];
  wire [4:0] dec_rs2_addr = dec_reg_inst[24:20];
  wire [4:0] dec_wbaddr = dec_reg_inst[11:7];
  wire [11:0] imm_itype = dec_reg_inst[31:20];
  wire [11:0] imm_stype = {dec_reg_inst[31:25],dec_wbaddr};
  wire [11:0] imm_sbtype = {dec_reg_inst[31],dec_reg_inst[7],dec_reg_inst[30:25],dec_reg_inst[11:8]};
  wire [19:0] imm_utype = dec_reg_inst[31:12];
  wire [19:0] imm_ujtype = {dec_reg_inst[31],dec_reg_inst[19:12],dec_reg_inst[20],dec_reg_inst[30:21]};
  wire [31:0] imm_z = {27'h0,dec_rs1_addr};
  wire [19:0] _imm_itype_sext_T_2 = imm_itype[11] ? 20'hfffff : 20'h0;
  wire [31:0] imm_itype_sext = {_imm_itype_sext_T_2,imm_itype};
  wire [19:0] _imm_stype_sext_T_2 = imm_stype[11] ? 20'hfffff : 20'h0;
  wire [31:0] imm_stype_sext = {_imm_stype_sext_T_2,dec_reg_inst[31:25],dec_wbaddr};
  wire [18:0] _imm_sbtype_sext_T_2 = imm_sbtype[11] ? 19'h7ffff : 19'h0;
  wire [31:0] imm_sbtype_sext = {_imm_sbtype_sext_T_2,dec_reg_inst[31],dec_reg_inst[7],dec_reg_inst[30:25],dec_reg_inst[
    11:8],1'h0};
  wire [31:0] imm_utype_sext = {imm_utype,12'h0};
  wire [10:0] _imm_ujtype_sext_T_2 = imm_ujtype[19] ? 11'h7ff : 11'h0;
  wire [31:0] imm_ujtype_sext = {_imm_ujtype_sext_T_2,dec_reg_inst[31],dec_reg_inst[19:12],dec_reg_inst[20],dec_reg_inst
    [30:21],1'h0};
  wire [31:0] _dec_alu_op2_T_6 = io_ctl_op2_sel == 3'h5 ? imm_ujtype_sext : 32'h0;
  wire [31:0] _dec_alu_op2_T_7 = io_ctl_op2_sel == 3'h4 ? imm_utype_sext : _dec_alu_op2_T_6;
  wire [31:0] _dec_alu_op2_T_8 = io_ctl_op2_sel == 3'h3 ? imm_sbtype_sext : _dec_alu_op2_T_7;
  wire [31:0] _dec_alu_op2_T_9 = io_ctl_op2_sel == 3'h2 ? imm_stype_sext : _dec_alu_op2_T_8;
  wire [31:0] _dec_alu_op2_T_10 = io_ctl_op2_sel == 3'h1 ? imm_itype_sext : _dec_alu_op2_T_9;
  wire [31:0] dec_alu_op2 = io_ctl_op2_sel == 3'h0 ? io_rf_read_rs2_data : _dec_alu_op2_T_10;
  wire [31:0] _dec_op1_data_T_14 = wb_reg_wbaddr == dec_rs1_addr & dec_rs1_addr != 5'h0 & wb_reg_ctrl_rf_wen ?
    wb_reg_wbdata : io_rf_read_rs1_data;
  wire [31:0] _mem_wbdata_T_4 = mem_reg_ctrl_wb_sel == 2'h3 ? csr_io_rw_rdata : mem_reg_alu_out;
  wire [31:0] _mem_wbdata_T_5 = mem_reg_ctrl_wb_sel == 2'h1 ? io_dmem_resp_bits_data : _mem_wbdata_T_4;
  wire [31:0] _mem_wbdata_T_6 = mem_reg_ctrl_wb_sel == 2'h2 ? mem_reg_alu_out : _mem_wbdata_T_5;
  wire [31:0] mem_wbdata = mem_reg_ctrl_wb_sel == 2'h0 ? mem_reg_alu_out : _mem_wbdata_T_6;
  wire [31:0] _dec_op1_data_T_15 = mem_reg_wbaddr == dec_rs1_addr & dec_rs1_addr != 5'h0 & mem_reg_ctrl_rf_wen ?
    mem_wbdata : _dec_op1_data_T_14;
  wire [31:0] _exe_alu_out_T_3 = exe_alu_op1 - brjmp_offset;
  wire [31:0] _exe_alu_out_T_5 = exe_alu_op1 & brjmp_offset;
  wire [31:0] _exe_alu_out_T_7 = exe_alu_op1 | brjmp_offset;
  wire [31:0] _exe_alu_out_T_9 = exe_alu_op1 ^ brjmp_offset;
  wire [31:0] _exe_alu_out_T_11 = exe_alu_op1;
  wire [31:0] _exe_alu_out_T_12 = brjmp_offset;
  wire [4:0] alu_shamt = brjmp_offset[4:0];
  wire [62:0] _GEN_1 = {{31'd0}, exe_alu_op1};
  wire [62:0] _exe_alu_out_T_17 = _GEN_1 << alu_shamt;
  wire [31:0] _exe_alu_out_T_22 = $signed(exe_alu_op1) >>> alu_shamt;
  wire [31:0] _exe_alu_out_T_24 = exe_alu_op1 >> alu_shamt;
  wire [31:0] _exe_alu_out_T_27 = exe_reg_ctrl_alu_fun == 4'hb ? brjmp_offset : exe_reg_inst;
  wire [31:0] _exe_alu_out_T_28 = exe_reg_ctrl_alu_fun == 4'ha ? exe_alu_op1 : _exe_alu_out_T_27;
  wire [31:0] _exe_alu_out_T_29 = exe_reg_ctrl_alu_fun == 4'h3 ? _exe_alu_out_T_24 : _exe_alu_out_T_28;
  wire [31:0] _exe_alu_out_T_30 = exe_reg_ctrl_alu_fun == 4'h4 ? _exe_alu_out_T_22 : _exe_alu_out_T_29;
  wire [31:0] _exe_alu_out_T_31 = exe_reg_ctrl_alu_fun == 4'h2 ? _exe_alu_out_T_17[31:0] : _exe_alu_out_T_30;
  wire [31:0] _exe_alu_out_T_32 = exe_reg_ctrl_alu_fun == 4'h9 ? {{31'd0}, exe_alu_op1 < brjmp_offset} :
    _exe_alu_out_T_31;
  wire [31:0] _exe_alu_out_T_33 = exe_reg_ctrl_alu_fun == 4'h8 ? {{31'd0}, $signed(_exe_alu_out_T_11) < $signed(
    _exe_alu_out_T_12)} : _exe_alu_out_T_32;
  wire [31:0] _exe_alu_out_T_34 = exe_reg_ctrl_alu_fun == 4'h7 ? _exe_alu_out_T_9 : _exe_alu_out_T_33;
  wire [31:0] _exe_alu_out_T_35 = exe_reg_ctrl_alu_fun == 4'h6 ? _exe_alu_out_T_7 : _exe_alu_out_T_34;
  wire [31:0] _exe_alu_out_T_36 = exe_reg_ctrl_alu_fun == 4'h5 ? _exe_alu_out_T_5 : _exe_alu_out_T_35;
  wire [31:0] _exe_alu_out_T_37 = exe_reg_ctrl_alu_fun == 4'h1 ? _exe_alu_out_T_3 : _exe_alu_out_T_36;
  wire [31:0] exe_alu_out = exe_reg_ctrl_alu_fun == 4'h0 ? exe_adder_out : _exe_alu_out_T_37;
  wire [31:0] _dec_op1_data_T_16 = exe_reg_wbaddr == dec_rs1_addr & dec_rs1_addr != 5'h0 & exe_reg_ctrl_rf_wen ?
    exe_alu_out : _dec_op1_data_T_15;
  wire [31:0] _dec_op2_data_T_18 = wb_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & wb_reg_ctrl_rf_wen &
    io_ctl_op2_sel == 3'h0 ? wb_reg_wbdata : dec_alu_op2;
  wire [31:0] _dec_rs2_data_T_12 = wb_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & wb_reg_ctrl_rf_wen ?
    wb_reg_wbdata : io_rf_read_rs2_data;
  wire [1:0] _GEN_15 = io_ctl_dec_kill ? 2'h0 : io_ctl_mem_fcn; // @[]
  wire [1:0] _GEN_33 = ~io_ctl_dec_stall & ~io_ctl_full_stall ? _GEN_15 : {{1'd0}, exe_reg_ctrl_mem_fcn}; // @[]
  wire [1:0] _GEN_42 = io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill ? 2'h0 : _GEN_33; // @[]
  wire [31:0] exe_pc_plus4 = exe_reg_pc + 32'h4;
  wire  _wb_reg_ctrl_rf_wen_T = io_ctl_mem_exception ? 1'h0 : mem_reg_ctrl_rf_wen;
  wire [1:0] _GEN_91 = reset ? 2'h0 : _GEN_42;
  CSRFile csr (
    .clock(csr_clock),
    .reset(csr_reset),
    .io_rw_cmd(csr_io_rw_cmd),
    .io_rw_rdata(csr_io_rw_rdata),
    .io_rw_wdata(csr_io_rw_wdata),
    .io_eret(csr_io_eret),
    .io_decode_csr(csr_io_decode_csr),
    .io_status_debug(csr_io_status_debug),
    .io_status_prv(csr_io_status_prv),
    .io_status_sd(csr_io_status_sd),
    .io_status_zero1(csr_io_status_zero1),
    .io_status_tsr(csr_io_status_tsr),
    .io_status_tw(csr_io_status_tw),
    .io_status_tvm(csr_io_status_tvm),
    .io_status_mxr(csr_io_status_mxr),
    .io_status_sum(csr_io_status_sum),
    .io_status_mprv(csr_io_status_mprv),
    .io_status_xs(csr_io_status_xs),
    .io_status_fs(csr_io_status_fs),
    .io_status_mpp(csr_io_status_mpp),
    .io_status_hpp(csr_io_status_hpp),
    .io_status_spp(csr_io_status_spp),
    .io_status_mpie(csr_io_status_mpie),
    .io_status_hpie(csr_io_status_hpie),
    .io_status_spie(csr_io_status_spie),
    .io_status_upie(csr_io_status_upie),
    .io_status_mie(csr_io_status_mie),
    .io_status_hie(csr_io_status_hie),
    .io_status_sie(csr_io_status_sie),
    .io_status_uie(csr_io_status_uie),
    .io_evec(csr_io_evec),
    .io_exception(csr_io_exception),
    .io_retire(csr_io_retire),
    .io_pc(csr_io_pc)
  );
  assign io_imem_req_bits_addr = if_reg_pc;
  assign io_dmem_req_valid = mem_reg_ctrl_mem_val;
  assign io_dmem_req_bits_addr = mem_reg_alu_out;
  assign io_dmem_req_bits_data = mem_reg_rs2_data;
  assign io_dmem_req_bits_fcn = mem_reg_ctrl_mem_fcn;
  assign io_dmem_req_bits_typ = mem_reg_ctrl_mem_typ;
  assign io_dat_dec_inst = dec_reg_inst;
  assign io_dat_exe_br_eq = exe_alu_op1 == exe_reg_rs2_data;
  assign io_dat_exe_br_lt = $signed(exe_alu_op1) < $signed(exe_reg_rs2_data);
  assign io_dat_exe_br_ltu = exe_alu_op1 < exe_reg_rs2_data;
  assign io_dat_exe_br_type = exe_reg_ctrl_br_type;
  assign io_dat_mem_ctrl_dmem_val = mem_reg_ctrl_mem_val;
  assign io_dat_csr_eret = csr_io_eret;
  assign io_rf_read_rs1_addr = dec_reg_inst[19:15];
  assign io_rf_read_rs2_addr = dec_reg_inst[24:20];
  assign io_rf_write_waddr = wb_reg_wbaddr;
  assign io_rf_write_wdata = wb_reg_wbdata;
  assign io_rf_write_wen = wb_reg_ctrl_rf_wen;
  assign csr_clock = clock;
  assign csr_reset = reset;
  assign csr_io_rw_cmd = mem_reg_ctrl_csr_cmd;
  assign csr_io_rw_wdata = mem_reg_alu_out;
  assign csr_io_decode_csr = mem_reg_inst[31:20];
  assign csr_io_exception = io_ctl_mem_exception;
  assign csr_io_retire = wb_reg_valid;
  assign csr_io_pc = mem_reg_pc;
  always @(posedge clock) begin
    if (reset) begin
      if_reg_pc <= 32'h80000000;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      if (!(io_ctl_fencei & io_ctl_exe_pc_sel == 2'h0 & ~io_ctl_dec_stall & ~io_ctl_full_stall & ~io_ctl_pipeline_kill
        )) begin
        if (io_ctl_exe_pc_sel == 2'h0) begin
          if_reg_pc <= if_pc_plus4;
        end else begin
          if_reg_pc <= _if_pc_next_T_4;
        end
      end
    end
    if (reset) begin
      dec_reg_valid <= 1'h0;
    end else if (io_ctl_pipeline_kill) begin
      dec_reg_valid <= 1'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_if_kill) begin
        dec_reg_valid <= 1'h0;
      end else begin
        dec_reg_valid <= 1'h1;
      end
    end
    if (reset) begin
      dec_reg_inst <= 32'h4033;
    end else if (io_ctl_pipeline_kill) begin
      dec_reg_inst <= 32'h4033;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_if_kill) begin
        dec_reg_inst <= 32'h4033;
      end else begin
        dec_reg_inst <= io_imem_resp_bits_data;
      end
    end
    if (reset) begin
      dec_reg_pc <= 32'h0;
    end else if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        dec_reg_pc <= if_reg_pc;
      end
    end
    if (reset) begin
      exe_reg_valid <= 1'h0;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_valid <= 1'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_valid <= 1'h0;
      end else begin
        exe_reg_valid <= dec_reg_valid;
      end
    end
    if (reset) begin
      exe_reg_inst <= 32'h4033;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_inst <= 32'h4033;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_inst <= 32'h4033;
      end else begin
        exe_reg_inst <= dec_reg_inst;
      end
    end
    if (reset) begin
      exe_reg_pc <= 32'h0;
    end else if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        exe_reg_pc <= dec_reg_pc;
      end
    end
    if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_wbaddr <= 5'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_wbaddr <= 5'h0;
      end else begin
        exe_reg_wbaddr <= dec_wbaddr;
      end
    end
    if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        if (io_ctl_op1_sel == 2'h2) begin
          exe_alu_op1 <= imm_z;
        end else if (io_ctl_op1_sel == 2'h1) begin
          exe_alu_op1 <= dec_reg_pc;
        end else begin
          exe_alu_op1 <= _dec_op1_data_T_16;
        end
      end
    end
    if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        if (exe_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & exe_reg_ctrl_rf_wen & io_ctl_op2_sel == 3'h0) begin
          if (exe_reg_ctrl_alu_fun == 4'h0) begin
            brjmp_offset <= exe_adder_out;
          end else begin
            brjmp_offset <= _exe_alu_out_T_37;
          end
        end else if (mem_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & mem_reg_ctrl_rf_wen & io_ctl_op2_sel == 3'h0
          ) begin
          brjmp_offset <= mem_wbdata;
        end else begin
          brjmp_offset <= _dec_op2_data_T_18;
        end
      end
    end
    if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        if (exe_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & exe_reg_ctrl_rf_wen) begin
          if (exe_reg_ctrl_alu_fun == 4'h0) begin
            exe_reg_rs2_data <= exe_adder_out;
          end else begin
            exe_reg_rs2_data <= _exe_alu_out_T_37;
          end
        end else if (mem_reg_wbaddr == dec_rs2_addr & dec_rs2_addr != 5'h0 & mem_reg_ctrl_rf_wen) begin
          exe_reg_rs2_data <= mem_wbdata;
        end else begin
          exe_reg_rs2_data <= _dec_rs2_data_T_12;
        end
      end
    end
    if (reset) begin
      exe_reg_ctrl_br_type <= 4'h0;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_ctrl_br_type <= 4'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_ctrl_br_type <= 4'h0;
      end else begin
        exe_reg_ctrl_br_type <= io_ctl_br_type;
      end
    end
    if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        exe_reg_ctrl_alu_fun <= io_ctl_alu_fun;
      end
    end
    if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        exe_reg_ctrl_wb_sel <= io_ctl_wb_sel;
      end
    end
    if (reset) begin
      exe_reg_ctrl_rf_wen <= 1'h0;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_ctrl_rf_wen <= 1'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_ctrl_rf_wen <= 1'h0;
      end else begin
        exe_reg_ctrl_rf_wen <= io_ctl_rf_wen;
      end
    end
    if (reset) begin
      exe_reg_ctrl_mem_val <= 1'h0;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_ctrl_mem_val <= 1'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_ctrl_mem_val <= 1'h0;
      end else begin
        exe_reg_ctrl_mem_val <= io_ctl_mem_val;
      end
    end
    exe_reg_ctrl_mem_fcn <= _GEN_91[0];
    if (reset) begin
      exe_reg_ctrl_mem_typ <= 3'h0;
    end else if (!(io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill)) begin
      if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
        if (!(io_ctl_dec_kill)) begin
          exe_reg_ctrl_mem_typ <= io_ctl_mem_typ;
        end
      end
    end
    if (reset) begin
      exe_reg_ctrl_csr_cmd <= 3'h0;
    end else if (io_ctl_dec_stall & ~io_ctl_full_stall | io_ctl_pipeline_kill) begin
      exe_reg_ctrl_csr_cmd <= 3'h0;
    end else if (~io_ctl_dec_stall & ~io_ctl_full_stall) begin
      if (io_ctl_dec_kill) begin
        exe_reg_ctrl_csr_cmd <= 3'h0;
      end else begin
        exe_reg_ctrl_csr_cmd <= io_ctl_csr_cmd;
      end
    end
    if (reset) begin
      mem_reg_valid <= 1'h0;
    end else if (io_ctl_pipeline_kill) begin
      mem_reg_valid <= 1'h0;
    end else if (~io_ctl_full_stall) begin
      mem_reg_valid <= exe_reg_valid;
    end
    if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_pc <= exe_reg_pc;
      end
    end
    if (io_ctl_pipeline_kill) begin
      mem_reg_inst <= 32'h4033;
    end else if (~io_ctl_full_stall) begin
      mem_reg_inst <= exe_reg_inst;
    end
    if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        if (exe_reg_ctrl_wb_sel == 2'h2) begin
          mem_reg_alu_out <= exe_pc_plus4;
        end else if (exe_reg_ctrl_alu_fun == 4'h0) begin
          mem_reg_alu_out <= exe_adder_out;
        end else begin
          mem_reg_alu_out <= _exe_alu_out_T_37;
        end
      end
    end
    if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_wbaddr <= exe_reg_wbaddr;
      end
    end
    if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_rs2_data <= exe_reg_rs2_data;
      end
    end
    if (reset) begin
      mem_reg_ctrl_rf_wen <= 1'h0;
    end else if (io_ctl_pipeline_kill) begin
      mem_reg_ctrl_rf_wen <= 1'h0;
    end else if (~io_ctl_full_stall) begin
      mem_reg_ctrl_rf_wen <= exe_reg_ctrl_rf_wen;
    end
    if (reset) begin
      mem_reg_ctrl_mem_val <= 1'h0;
    end else if (io_ctl_pipeline_kill) begin
      mem_reg_ctrl_mem_val <= 1'h0;
    end else if (~io_ctl_full_stall) begin
      mem_reg_ctrl_mem_val <= exe_reg_ctrl_mem_val;
    end
    if (reset) begin
      mem_reg_ctrl_mem_fcn <= 1'h0;
    end else if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_ctrl_mem_fcn <= exe_reg_ctrl_mem_fcn;
      end
    end
    if (reset) begin
      mem_reg_ctrl_mem_typ <= 3'h0;
    end else if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_ctrl_mem_typ <= exe_reg_ctrl_mem_typ;
      end
    end
    if (!(io_ctl_pipeline_kill)) begin
      if (~io_ctl_full_stall) begin
        mem_reg_ctrl_wb_sel <= exe_reg_ctrl_wb_sel;
      end
    end
    if (reset) begin
      mem_reg_ctrl_csr_cmd <= 3'h0;
    end else if (io_ctl_pipeline_kill) begin
      mem_reg_ctrl_csr_cmd <= 3'h0;
    end else if (~io_ctl_full_stall) begin
      mem_reg_ctrl_csr_cmd <= exe_reg_ctrl_csr_cmd;
    end
    if (reset) begin
      wb_reg_valid <= 1'h0;
    end else begin
      wb_reg_valid <= ~io_ctl_full_stall & (mem_reg_valid & ~io_ctl_mem_exception);
    end
    if (~io_ctl_full_stall) begin
      wb_reg_wbaddr <= mem_reg_wbaddr;
    end
    if (~io_ctl_full_stall) begin
      if (mem_reg_ctrl_wb_sel == 2'h0) begin
        wb_reg_wbdata <= mem_reg_alu_out;
      end else if (mem_reg_ctrl_wb_sel == 2'h2) begin
        wb_reg_wbdata <= mem_reg_alu_out;
      end else if (mem_reg_ctrl_wb_sel == 2'h1) begin
        wb_reg_wbdata <= io_dmem_resp_bits_data;
      end else begin
        wb_reg_wbdata <= _mem_wbdata_T_4;
      end
    end
    if (reset) begin
      wb_reg_ctrl_rf_wen <= 1'h0;
    end else begin
      wb_reg_ctrl_rf_wen <= ~io_ctl_full_stall & _wb_reg_ctrl_rf_wen_T;
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  if_reg_pc = _RAND_0[31:0];
  _RAND_1 = {1{`RANDOM}};
  dec_reg_valid = _RAND_1[0:0];
  _RAND_2 = {1{`RANDOM}};
  dec_reg_inst = _RAND_2[31:0];
  _RAND_3 = {1{`RANDOM}};
  dec_reg_pc = _RAND_3[31:0];
  _RAND_4 = {1{`RANDOM}};
  exe_reg_valid = _RAND_4[0:0];
  _RAND_5 = {1{`RANDOM}};
  exe_reg_inst = _RAND_5[31:0];
  _RAND_6 = {1{`RANDOM}};
  exe_reg_pc = _RAND_6[31:0];
  _RAND_7 = {1{`RANDOM}};
  exe_reg_wbaddr = _RAND_7[4:0];
  _RAND_8 = {1{`RANDOM}};
  exe_alu_op1 = _RAND_8[31:0];
  _RAND_9 = {1{`RANDOM}};
  brjmp_offset = _RAND_9[31:0];
  _RAND_10 = {1{`RANDOM}};
  exe_reg_rs2_data = _RAND_10[31:0];
  _RAND_11 = {1{`RANDOM}};
  exe_reg_ctrl_br_type = _RAND_11[3:0];
  _RAND_12 = {1{`RANDOM}};
  exe_reg_ctrl_alu_fun = _RAND_12[3:0];
  _RAND_13 = {1{`RANDOM}};
  exe_reg_ctrl_wb_sel = _RAND_13[1:0];
  _RAND_14 = {1{`RANDOM}};
  exe_reg_ctrl_rf_wen = _RAND_14[0:0];
  _RAND_15 = {1{`RANDOM}};
  exe_reg_ctrl_mem_val = _RAND_15[0:0];
  _RAND_16 = {1{`RANDOM}};
  exe_reg_ctrl_mem_fcn = _RAND_16[0:0];
  _RAND_17 = {1{`RANDOM}};
  exe_reg_ctrl_mem_typ = _RAND_17[2:0];
  _RAND_18 = {1{`RANDOM}};
  exe_reg_ctrl_csr_cmd = _RAND_18[2:0];
  _RAND_19 = {1{`RANDOM}};
  mem_reg_valid = _RAND_19[0:0];
  _RAND_20 = {1{`RANDOM}};
  mem_reg_pc = _RAND_20[31:0];
  _RAND_21 = {1{`RANDOM}};
  mem_reg_inst = _RAND_21[31:0];
  _RAND_22 = {1{`RANDOM}};
  mem_reg_alu_out = _RAND_22[31:0];
  _RAND_23 = {1{`RANDOM}};
  mem_reg_wbaddr = _RAND_23[4:0];
  _RAND_24 = {1{`RANDOM}};
  mem_reg_rs2_data = _RAND_24[31:0];
  _RAND_25 = {1{`RANDOM}};
  mem_reg_ctrl_rf_wen = _RAND_25[0:0];
  _RAND_26 = {1{`RANDOM}};
  mem_reg_ctrl_mem_val = _RAND_26[0:0];
  _RAND_27 = {1{`RANDOM}};
  mem_reg_ctrl_mem_fcn = _RAND_27[0:0];
  _RAND_28 = {1{`RANDOM}};
  mem_reg_ctrl_mem_typ = _RAND_28[2:0];
  _RAND_29 = {1{`RANDOM}};
  mem_reg_ctrl_wb_sel = _RAND_29[1:0];
  _RAND_30 = {1{`RANDOM}};
  mem_reg_ctrl_csr_cmd = _RAND_30[2:0];
  _RAND_31 = {1{`RANDOM}};
  wb_reg_valid = _RAND_31[0:0];
  _RAND_32 = {1{`RANDOM}};
  wb_reg_wbaddr = _RAND_32[4:0];
  _RAND_33 = {1{`RANDOM}};
  wb_reg_wbdata = _RAND_33[31:0];
  _RAND_34 = {1{`RANDOM}};
  wb_reg_ctrl_rf_wen = _RAND_34[0:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module Core(
  input         clock,
  input         reset,
  output [31:0] io_imem_req_bits_addr,
  input  [31:0] io_imem_resp_bits_data,
  output        io_dmem_req_valid,
  output [31:0] io_dmem_req_bits_addr,
  output [31:0] io_dmem_req_bits_data,
  output        io_dmem_req_bits_fcn,
  output [2:0]  io_dmem_req_bits_typ,
  input         io_dmem_resp_valid,
  input  [31:0] io_dmem_resp_bits_data,
  output [4:0]  io_rf_read_rs1_addr,
  input  [31:0] io_rf_read_rs1_data,
  output [4:0]  io_rf_read_rs2_addr,
  input  [31:0] io_rf_read_rs2_data,
  output [4:0]  io_rf_write_waddr,
  output [31:0] io_rf_write_wdata,
  output        io_rf_write_wen
);
  wire  c_clock;
  wire  c_reset;
  wire  c_io_dmem_resp_valid;
  wire [31:0] c_io_dat_dec_inst;
  wire  c_io_dat_exe_br_eq;
  wire  c_io_dat_exe_br_lt;
  wire  c_io_dat_exe_br_ltu;
  wire [3:0] c_io_dat_exe_br_type;
  wire  c_io_dat_mem_ctrl_dmem_val;
  wire  c_io_dat_csr_eret;
  wire  c_io_ctl_dec_stall;
  wire  c_io_ctl_full_stall;
  wire [1:0] c_io_ctl_exe_pc_sel;
  wire [3:0] c_io_ctl_br_type;
  wire  c_io_ctl_if_kill;
  wire  c_io_ctl_dec_kill;
  wire [1:0] c_io_ctl_op1_sel;
  wire [2:0] c_io_ctl_op2_sel;
  wire [3:0] c_io_ctl_alu_fun;
  wire [1:0] c_io_ctl_wb_sel;
  wire  c_io_ctl_rf_wen;
  wire  c_io_ctl_mem_val;
  wire [1:0] c_io_ctl_mem_fcn;
  wire [2:0] c_io_ctl_mem_typ;
  wire [2:0] c_io_ctl_csr_cmd;
  wire  c_io_ctl_fencei;
  wire  c_io_ctl_pipeline_kill;
  wire  c_io_ctl_mem_exception;
  wire  d_clock;
  wire  d_reset;
  wire [31:0] d_io_imem_req_bits_addr;
  wire [31:0] d_io_imem_resp_bits_data;
  wire  d_io_dmem_req_valid;
  wire [31:0] d_io_dmem_req_bits_addr;
  wire [31:0] d_io_dmem_req_bits_data;
  wire  d_io_dmem_req_bits_fcn;
  wire [2:0] d_io_dmem_req_bits_typ;
  wire [31:0] d_io_dmem_resp_bits_data;
  wire  d_io_ctl_dec_stall;
  wire  d_io_ctl_full_stall;
  wire [1:0] d_io_ctl_exe_pc_sel;
  wire [3:0] d_io_ctl_br_type;
  wire  d_io_ctl_if_kill;
  wire  d_io_ctl_dec_kill;
  wire [1:0] d_io_ctl_op1_sel;
  wire [2:0] d_io_ctl_op2_sel;
  wire [3:0] d_io_ctl_alu_fun;
  wire [1:0] d_io_ctl_wb_sel;
  wire  d_io_ctl_rf_wen;
  wire  d_io_ctl_mem_val;
  wire [1:0] d_io_ctl_mem_fcn;
  wire [2:0] d_io_ctl_mem_typ;
  wire [2:0] d_io_ctl_csr_cmd;
  wire  d_io_ctl_fencei;
  wire  d_io_ctl_pipeline_kill;
  wire  d_io_ctl_mem_exception;
  wire [31:0] d_io_dat_dec_inst;
  wire  d_io_dat_exe_br_eq;
  wire  d_io_dat_exe_br_lt;
  wire  d_io_dat_exe_br_ltu;
  wire [3:0] d_io_dat_exe_br_type;
  wire  d_io_dat_mem_ctrl_dmem_val;
  wire  d_io_dat_csr_eret;
  wire [4:0] d_io_rf_read_rs1_addr;
  wire [31:0] d_io_rf_read_rs1_data;
  wire [4:0] d_io_rf_read_rs2_addr;
  wire [31:0] d_io_rf_read_rs2_data;
  wire [4:0] d_io_rf_write_waddr;
  wire [31:0] d_io_rf_write_wdata;
  wire  d_io_rf_write_wen;
  CtlPath c (
    .clock(c_clock),
    .reset(c_reset),
    .io_dmem_resp_valid(c_io_dmem_resp_valid),
    .io_dat_dec_inst(c_io_dat_dec_inst),
    .io_dat_exe_br_eq(c_io_dat_exe_br_eq),
    .io_dat_exe_br_lt(c_io_dat_exe_br_lt),
    .io_dat_exe_br_ltu(c_io_dat_exe_br_ltu),
    .io_dat_exe_br_type(c_io_dat_exe_br_type),
    .io_dat_mem_ctrl_dmem_val(c_io_dat_mem_ctrl_dmem_val),
    .io_dat_csr_eret(c_io_dat_csr_eret),
    .io_ctl_dec_stall(c_io_ctl_dec_stall),
    .io_ctl_full_stall(c_io_ctl_full_stall),
    .io_ctl_exe_pc_sel(c_io_ctl_exe_pc_sel),
    .io_ctl_br_type(c_io_ctl_br_type),
    .io_ctl_if_kill(c_io_ctl_if_kill),
    .io_ctl_dec_kill(c_io_ctl_dec_kill),
    .io_ctl_op1_sel(c_io_ctl_op1_sel),
    .io_ctl_op2_sel(c_io_ctl_op2_sel),
    .io_ctl_alu_fun(c_io_ctl_alu_fun),
    .io_ctl_wb_sel(c_io_ctl_wb_sel),
    .io_ctl_rf_wen(c_io_ctl_rf_wen),
    .io_ctl_mem_val(c_io_ctl_mem_val),
    .io_ctl_mem_fcn(c_io_ctl_mem_fcn),
    .io_ctl_mem_typ(c_io_ctl_mem_typ),
    .io_ctl_csr_cmd(c_io_ctl_csr_cmd),
    .io_ctl_fencei(c_io_ctl_fencei),
    .io_ctl_pipeline_kill(c_io_ctl_pipeline_kill),
    .io_ctl_mem_exception(c_io_ctl_mem_exception)
  );
  DatPath d (
    .clock(d_clock),
    .reset(d_reset),
    .io_imem_req_bits_addr(d_io_imem_req_bits_addr),
    .io_imem_resp_bits_data(d_io_imem_resp_bits_data),
    .io_dmem_req_valid(d_io_dmem_req_valid),
    .io_dmem_req_bits_addr(d_io_dmem_req_bits_addr),
    .io_dmem_req_bits_data(d_io_dmem_req_bits_data),
    .io_dmem_req_bits_fcn(d_io_dmem_req_bits_fcn),
    .io_dmem_req_bits_typ(d_io_dmem_req_bits_typ),
    .io_dmem_resp_bits_data(d_io_dmem_resp_bits_data),
    .io_ctl_dec_stall(d_io_ctl_dec_stall),
    .io_ctl_full_stall(d_io_ctl_full_stall),
    .io_ctl_exe_pc_sel(d_io_ctl_exe_pc_sel),
    .io_ctl_br_type(d_io_ctl_br_type),
    .io_ctl_if_kill(d_io_ctl_if_kill),
    .io_ctl_dec_kill(d_io_ctl_dec_kill),
    .io_ctl_op1_sel(d_io_ctl_op1_sel),
    .io_ctl_op2_sel(d_io_ctl_op2_sel),
    .io_ctl_alu_fun(d_io_ctl_alu_fun),
    .io_ctl_wb_sel(d_io_ctl_wb_sel),
    .io_ctl_rf_wen(d_io_ctl_rf_wen),
    .io_ctl_mem_val(d_io_ctl_mem_val),
    .io_ctl_mem_fcn(d_io_ctl_mem_fcn),
    .io_ctl_mem_typ(d_io_ctl_mem_typ),
    .io_ctl_csr_cmd(d_io_ctl_csr_cmd),
    .io_ctl_fencei(d_io_ctl_fencei),
    .io_ctl_pipeline_kill(d_io_ctl_pipeline_kill),
    .io_ctl_mem_exception(d_io_ctl_mem_exception),
    .io_dat_dec_inst(d_io_dat_dec_inst),
    .io_dat_exe_br_eq(d_io_dat_exe_br_eq),
    .io_dat_exe_br_lt(d_io_dat_exe_br_lt),
    .io_dat_exe_br_ltu(d_io_dat_exe_br_ltu),
    .io_dat_exe_br_type(d_io_dat_exe_br_type),
    .io_dat_mem_ctrl_dmem_val(d_io_dat_mem_ctrl_dmem_val),
    .io_dat_csr_eret(d_io_dat_csr_eret),
    .io_rf_read_rs1_addr(d_io_rf_read_rs1_addr),
    .io_rf_read_rs1_data(d_io_rf_read_rs1_data),
    .io_rf_read_rs2_addr(d_io_rf_read_rs2_addr),
    .io_rf_read_rs2_data(d_io_rf_read_rs2_data),
    .io_rf_write_waddr(d_io_rf_write_waddr),
    .io_rf_write_wdata(d_io_rf_write_wdata),
    .io_rf_write_wen(d_io_rf_write_wen)
  );
  assign io_imem_req_bits_addr = d_io_imem_req_bits_addr;
  assign io_dmem_req_valid = d_io_dmem_req_valid;
  assign io_dmem_req_bits_addr = d_io_dmem_req_bits_addr;
  assign io_dmem_req_bits_data = d_io_dmem_req_bits_data;
  assign io_dmem_req_bits_fcn = d_io_dmem_req_bits_fcn;
  assign io_dmem_req_bits_typ = d_io_dmem_req_bits_typ;
  assign io_rf_read_rs1_addr = d_io_rf_read_rs1_addr;
  assign io_rf_read_rs2_addr = d_io_rf_read_rs2_addr;
  assign io_rf_write_waddr = d_io_rf_write_waddr;
  assign io_rf_write_wdata = d_io_rf_write_wdata;
  assign io_rf_write_wen = d_io_rf_write_wen;
  assign c_clock = clock;
  assign c_reset = reset;
  assign c_io_dmem_resp_valid = io_dmem_resp_valid;
  assign c_io_dat_dec_inst = d_io_dat_dec_inst;
  assign c_io_dat_exe_br_eq = d_io_dat_exe_br_eq;
  assign c_io_dat_exe_br_lt = d_io_dat_exe_br_lt;
  assign c_io_dat_exe_br_ltu = d_io_dat_exe_br_ltu;
  assign c_io_dat_exe_br_type = d_io_dat_exe_br_type;
  assign c_io_dat_mem_ctrl_dmem_val = d_io_dat_mem_ctrl_dmem_val;
  assign c_io_dat_csr_eret = d_io_dat_csr_eret;
  assign d_clock = clock;
  assign d_reset = reset;
  assign d_io_imem_resp_bits_data = io_imem_resp_bits_data;
  assign d_io_dmem_resp_bits_data = io_dmem_resp_bits_data;
  assign d_io_ctl_dec_stall = c_io_ctl_dec_stall;
  assign d_io_ctl_full_stall = c_io_ctl_full_stall;
  assign d_io_ctl_exe_pc_sel = c_io_ctl_exe_pc_sel;
  assign d_io_ctl_br_type = c_io_ctl_br_type;
  assign d_io_ctl_if_kill = c_io_ctl_if_kill;
  assign d_io_ctl_dec_kill = c_io_ctl_dec_kill;
  assign d_io_ctl_op1_sel = c_io_ctl_op1_sel;
  assign d_io_ctl_op2_sel = c_io_ctl_op2_sel;
  assign d_io_ctl_alu_fun = c_io_ctl_alu_fun;
  assign d_io_ctl_wb_sel = c_io_ctl_wb_sel;
  assign d_io_ctl_rf_wen = c_io_ctl_rf_wen;
  assign d_io_ctl_mem_val = c_io_ctl_mem_val;
  assign d_io_ctl_mem_fcn = c_io_ctl_mem_fcn;
  assign d_io_ctl_mem_typ = c_io_ctl_mem_typ;
  assign d_io_ctl_csr_cmd = c_io_ctl_csr_cmd;
  assign d_io_ctl_fencei = c_io_ctl_fencei;
  assign d_io_ctl_pipeline_kill = c_io_ctl_pipeline_kill;
  assign d_io_ctl_mem_exception = c_io_ctl_mem_exception;
  assign d_io_rf_read_rs1_data = io_rf_read_rs1_data;
  assign d_io_rf_read_rs2_data = io_rf_read_rs2_data;
endmodule
module SodorTile(
  input         clock,
  input         reset,
  output [31:0] io_imem_req_bits_addr,
  input  [31:0] io_imem_resp_bits_data,
  output        io_dmem_req_valid,
  output [31:0] io_dmem_req_bits_addr,
  output [31:0] io_dmem_req_bits_data,
  output        io_dmem_req_bits_fcn,
  output [2:0]  io_dmem_req_bits_typ,
  input         io_dmem_resp_valid,
  input  [31:0] io_dmem_resp_bits_data,
  output [4:0]  io_rf_read_rs1_addr,
  input  [31:0] io_rf_read_rs1_data,
  output [4:0]  io_rf_read_rs2_addr,
  input  [31:0] io_rf_read_rs2_data,
  output [4:0]  io_rf_write_waddr,
  output [31:0] io_rf_write_wdata,
  output        io_rf_write_wen
);
  wire  core_clock;
  wire  core_reset;
  wire [31:0] core_io_imem_req_bits_addr;
  wire [31:0] core_io_imem_resp_bits_data;
  wire  core_io_dmem_req_valid;
  wire [31:0] core_io_dmem_req_bits_addr;
  wire [31:0] core_io_dmem_req_bits_data;
  wire  core_io_dmem_req_bits_fcn;
  wire [2:0] core_io_dmem_req_bits_typ;
  wire  core_io_dmem_resp_valid;
  wire [31:0] core_io_dmem_resp_bits_data;
  wire [4:0] core_io_rf_read_rs1_addr;
  wire [31:0] core_io_rf_read_rs1_data;
  wire [4:0] core_io_rf_read_rs2_addr;
  wire [31:0] core_io_rf_read_rs2_data;
  wire [4:0] core_io_rf_write_waddr;
  wire [31:0] core_io_rf_write_wdata;
  wire  core_io_rf_write_wen;
  Core core (
    .clock(core_clock),
    .reset(core_reset),
    .io_imem_req_bits_addr(core_io_imem_req_bits_addr),
    .io_imem_resp_bits_data(core_io_imem_resp_bits_data),
    .io_dmem_req_valid(core_io_dmem_req_valid),
    .io_dmem_req_bits_addr(core_io_dmem_req_bits_addr),
    .io_dmem_req_bits_data(core_io_dmem_req_bits_data),
    .io_dmem_req_bits_fcn(core_io_dmem_req_bits_fcn),
    .io_dmem_req_bits_typ(core_io_dmem_req_bits_typ),
    .io_dmem_resp_valid(core_io_dmem_resp_valid),
    .io_dmem_resp_bits_data(core_io_dmem_resp_bits_data),
    .io_rf_read_rs1_addr(core_io_rf_read_rs1_addr),
    .io_rf_read_rs1_data(core_io_rf_read_rs1_data),
    .io_rf_read_rs2_addr(core_io_rf_read_rs2_addr),
    .io_rf_read_rs2_data(core_io_rf_read_rs2_data),
    .io_rf_write_waddr(core_io_rf_write_waddr),
    .io_rf_write_wdata(core_io_rf_write_wdata),
    .io_rf_write_wen(core_io_rf_write_wen)
  );
  assign io_imem_req_bits_addr = core_io_imem_req_bits_addr;
  assign io_dmem_req_valid = core_io_dmem_req_valid;
  assign io_dmem_req_bits_addr = core_io_dmem_req_bits_addr;
  assign io_dmem_req_bits_data = core_io_dmem_req_bits_data;
  assign io_dmem_req_bits_fcn = core_io_dmem_req_bits_fcn;
  assign io_dmem_req_bits_typ = core_io_dmem_req_bits_typ;
  assign io_rf_read_rs1_addr = core_io_rf_read_rs1_addr;
  assign io_rf_read_rs2_addr = core_io_rf_read_rs2_addr;
  assign io_rf_write_waddr = core_io_rf_write_waddr;
  assign io_rf_write_wdata = core_io_rf_write_wdata;
  assign io_rf_write_wen = core_io_rf_write_wen;
  assign core_clock = clock;
  assign core_reset = reset;
  assign core_io_imem_resp_bits_data = io_imem_resp_bits_data;
  assign core_io_dmem_resp_valid = io_dmem_resp_valid;
  assign core_io_dmem_resp_bits_data = io_dmem_resp_bits_data;
  assign core_io_rf_read_rs1_data = io_rf_read_rs1_data;
  assign core_io_rf_read_rs2_data = io_rf_read_rs2_data;
endmodule
module SodorFullChipMemory(
  input         clock,
  input         io_core_0_req_valid,
  input  [31:0] io_core_0_req_bits_addr,
  input  [31:0] io_core_0_req_bits_data,
  input         io_core_0_req_bits_fcn,
  input  [2:0]  io_core_0_req_bits_typ,
  output        io_core_0_resp_valid,
  output [31:0] io_core_0_resp_bits_data,
  input  [31:0] io_core_1_req_bits_addr,
  output [31:0] io_core_1_resp_bits_data,
  input         io_host_valid,
  input         io_host_write,
  input  [31:0] io_host_addr,
  input  [31:0] io_host_wdata,
  output [31:0] io_host_rdata,
  output [31:0] io_tohost
);
`ifdef RANDOMIZE_MEM_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_MEM_INIT
  reg [7:0] bytes [0:2097151];
  wire  bytes_draw_MPORT_en;
  wire [20:0] bytes_draw_MPORT_addr;
  wire [7:0] bytes_draw_MPORT_data;
  wire  bytes_draw_MPORT_1_en;
  wire [20:0] bytes_draw_MPORT_1_addr;
  wire [7:0] bytes_draw_MPORT_1_data;
  wire  bytes_draw_MPORT_2_en;
  wire [20:0] bytes_draw_MPORT_2_addr;
  wire [7:0] bytes_draw_MPORT_2_data;
  wire  bytes_draw_MPORT_3_en;
  wire [20:0] bytes_draw_MPORT_3_addr;
  wire [7:0] bytes_draw_MPORT_3_data;
  wire  bytes_io_core_1_resp_bits_data_MPORT_en;
  wire [20:0] bytes_io_core_1_resp_bits_data_MPORT_addr;
  wire [7:0] bytes_io_core_1_resp_bits_data_MPORT_data;
  wire  bytes_io_core_1_resp_bits_data_MPORT_1_en;
  wire [20:0] bytes_io_core_1_resp_bits_data_MPORT_1_addr;
  wire [7:0] bytes_io_core_1_resp_bits_data_MPORT_1_data;
  wire  bytes_io_core_1_resp_bits_data_MPORT_2_en;
  wire [20:0] bytes_io_core_1_resp_bits_data_MPORT_2_addr;
  wire [7:0] bytes_io_core_1_resp_bits_data_MPORT_2_data;
  wire  bytes_io_core_1_resp_bits_data_MPORT_3_en;
  wire [20:0] bytes_io_core_1_resp_bits_data_MPORT_3_addr;
  wire [7:0] bytes_io_core_1_resp_bits_data_MPORT_3_data;
  wire  bytes_io_host_rdata_MPORT_en;
  wire [20:0] bytes_io_host_rdata_MPORT_addr;
  wire [7:0] bytes_io_host_rdata_MPORT_data;
  wire  bytes_io_host_rdata_MPORT_1_en;
  wire [20:0] bytes_io_host_rdata_MPORT_1_addr;
  wire [7:0] bytes_io_host_rdata_MPORT_1_data;
  wire  bytes_io_host_rdata_MPORT_2_en;
  wire [20:0] bytes_io_host_rdata_MPORT_2_addr;
  wire [7:0] bytes_io_host_rdata_MPORT_2_data;
  wire  bytes_io_host_rdata_MPORT_3_en;
  wire [20:0] bytes_io_host_rdata_MPORT_3_addr;
  wire [7:0] bytes_io_host_rdata_MPORT_3_data;
  wire  bytes_io_tohost_MPORT_en;
  wire [20:0] bytes_io_tohost_MPORT_addr;
  wire [7:0] bytes_io_tohost_MPORT_data;
  wire  bytes_io_tohost_MPORT_1_en;
  wire [20:0] bytes_io_tohost_MPORT_1_addr;
  wire [7:0] bytes_io_tohost_MPORT_1_data;
  wire  bytes_io_tohost_MPORT_2_en;
  wire [20:0] bytes_io_tohost_MPORT_2_addr;
  wire [7:0] bytes_io_tohost_MPORT_2_data;
  wire  bytes_io_tohost_MPORT_3_en;
  wire [20:0] bytes_io_tohost_MPORT_3_addr;
  wire [7:0] bytes_io_tohost_MPORT_3_data;
  wire [7:0] bytes_MPORT_data;
  wire [20:0] bytes_MPORT_addr;
  wire  bytes_MPORT_mask;
  wire  bytes_MPORT_en;
  wire [7:0] bytes_MPORT_1_data;
  wire [20:0] bytes_MPORT_1_addr;
  wire  bytes_MPORT_1_mask;
  wire  bytes_MPORT_1_en;
  wire [7:0] bytes_MPORT_2_data;
  wire [20:0] bytes_MPORT_2_addr;
  wire  bytes_MPORT_2_mask;
  wire  bytes_MPORT_2_en;
  wire [7:0] bytes_MPORT_3_data;
  wire [20:0] bytes_MPORT_3_addr;
  wire  bytes_MPORT_3_mask;
  wire  bytes_MPORT_3_en;
  wire [7:0] bytes_MPORT_4_data;
  wire [20:0] bytes_MPORT_4_addr;
  wire  bytes_MPORT_4_mask;
  wire  bytes_MPORT_4_en;
  wire [7:0] bytes_MPORT_5_data;
  wire [20:0] bytes_MPORT_5_addr;
  wire  bytes_MPORT_5_mask;
  wire  bytes_MPORT_5_en;
  wire [7:0] bytes_MPORT_6_data;
  wire [20:0] bytes_MPORT_6_addr;
  wire  bytes_MPORT_6_mask;
  wire  bytes_MPORT_6_en;
  wire [7:0] bytes_MPORT_7_data;
  wire [20:0] bytes_MPORT_7_addr;
  wire  bytes_MPORT_7_mask;
  wire  bytes_MPORT_7_en;
  wire [20:0] draw_base = io_core_0_req_bits_addr[20:0];
  wire [21:0] _draw_T_9 = {{1'd0}, draw_base};
  wire [31:0] draw = {bytes_draw_MPORT_data,bytes_draw_MPORT_1_data,bytes_draw_MPORT_2_data,bytes_draw_MPORT_3_data};
  wire [23:0] _io_core_0_resp_bits_data_T_2 = draw[7] ? 24'hffffff : 24'h0;
  wire [31:0] _io_core_0_resp_bits_data_T_4 = {_io_core_0_resp_bits_data_T_2,draw[7:0]};
  wire [15:0] _io_core_0_resp_bits_data_T_7 = draw[15] ? 16'hffff : 16'h0;
  wire [31:0] _io_core_0_resp_bits_data_T_9 = {_io_core_0_resp_bits_data_T_7,draw[15:0]};
  wire [31:0] _io_core_0_resp_bits_data_T_11 = {24'h0,draw[7:0]};
  wire [31:0] _io_core_0_resp_bits_data_T_13 = {16'h0,draw[15:0]};
  wire [31:0] _io_core_0_resp_bits_data_T_15 = 3'h1 == io_core_0_req_bits_typ ? _io_core_0_resp_bits_data_T_4 : draw;
  wire [31:0] _io_core_0_resp_bits_data_T_17 = 3'h2 == io_core_0_req_bits_typ ? _io_core_0_resp_bits_data_T_9 :
    _io_core_0_resp_bits_data_T_15;
  wire [31:0] _io_core_0_resp_bits_data_T_19 = 3'h5 == io_core_0_req_bits_typ ? _io_core_0_resp_bits_data_T_11 :
    _io_core_0_resp_bits_data_T_17;
  wire [20:0] io_core_1_resp_bits_data_base = io_core_1_req_bits_addr[20:0];
  wire [21:0] _io_core_1_resp_bits_data_T_9 = {{1'd0}, io_core_1_resp_bits_data_base};
  wire [15:0] io_core_1_resp_bits_data_lo = {bytes_io_core_1_resp_bits_data_MPORT_2_data,
    bytes_io_core_1_resp_bits_data_MPORT_3_data};
  wire [15:0] io_core_1_resp_bits_data_hi = {bytes_io_core_1_resp_bits_data_MPORT_data,
    bytes_io_core_1_resp_bits_data_MPORT_1_data};
  wire [2:0] _storeBytes_T_1 = 3'h1 == io_core_0_req_bits_typ ? 3'h1 : 3'h4;
  wire [2:0] storeBytes = 3'h2 == io_core_0_req_bits_typ ? 3'h2 : _storeBytes_T_1;
  wire [32:0] _T_5 = {{1'd0}, io_core_0_req_bits_addr};
  wire [31:0] _T_11 = io_core_0_req_bits_addr + 32'h1;
  wire [31:0] _T_16 = io_core_0_req_bits_addr + 32'h2;
  wire [31:0] _T_21 = io_core_0_req_bits_addr + 32'h3;
  wire [20:0] io_host_rdata_base = io_host_addr[20:0];
  wire [21:0] _io_host_rdata_T_9 = {{1'd0}, io_host_rdata_base};
  wire [15:0] io_host_rdata_lo = {bytes_io_host_rdata_MPORT_2_data,bytes_io_host_rdata_MPORT_3_data};
  wire [15:0] io_host_rdata_hi = {bytes_io_host_rdata_MPORT_data,bytes_io_host_rdata_MPORT_1_data};
  wire [32:0] _T_25 = {{1'd0}, io_host_addr};
  wire [31:0] _T_30 = io_host_addr + 32'h1;
  wire [31:0] _T_34 = io_host_addr + 32'h2;
  wire [31:0] _T_38 = io_host_addr + 32'h3;
  wire [15:0] io_tohost_lo = {bytes_io_tohost_MPORT_2_data,bytes_io_tohost_MPORT_3_data};
  wire [15:0] io_tohost_hi = {bytes_io_tohost_MPORT_data,bytes_io_tohost_MPORT_1_data};
  assign bytes_draw_MPORT_en = 1'h1;
  assign bytes_draw_MPORT_addr = draw_base + 21'h3;
  assign bytes_draw_MPORT_data = bytes[bytes_draw_MPORT_addr];
  assign bytes_draw_MPORT_1_en = 1'h1;
  assign bytes_draw_MPORT_1_addr = draw_base + 21'h2;
  assign bytes_draw_MPORT_1_data = bytes[bytes_draw_MPORT_1_addr];
  assign bytes_draw_MPORT_2_en = 1'h1;
  assign bytes_draw_MPORT_2_addr = draw_base + 21'h1;
  assign bytes_draw_MPORT_2_data = bytes[bytes_draw_MPORT_2_addr];
  assign bytes_draw_MPORT_3_en = 1'h1;
  assign bytes_draw_MPORT_3_addr = _draw_T_9[20:0];
  assign bytes_draw_MPORT_3_data = bytes[bytes_draw_MPORT_3_addr];
  assign bytes_io_core_1_resp_bits_data_MPORT_en = 1'h1;
  assign bytes_io_core_1_resp_bits_data_MPORT_addr = io_core_1_resp_bits_data_base + 21'h3;
  assign bytes_io_core_1_resp_bits_data_MPORT_data = bytes[bytes_io_core_1_resp_bits_data_MPORT_addr];
  assign bytes_io_core_1_resp_bits_data_MPORT_1_en = 1'h1;
  assign bytes_io_core_1_resp_bits_data_MPORT_1_addr = io_core_1_resp_bits_data_base + 21'h2;
  assign bytes_io_core_1_resp_bits_data_MPORT_1_data = bytes[bytes_io_core_1_resp_bits_data_MPORT_1_addr];
  assign bytes_io_core_1_resp_bits_data_MPORT_2_en = 1'h1;
  assign bytes_io_core_1_resp_bits_data_MPORT_2_addr = io_core_1_resp_bits_data_base + 21'h1;
  assign bytes_io_core_1_resp_bits_data_MPORT_2_data = bytes[bytes_io_core_1_resp_bits_data_MPORT_2_addr];
  assign bytes_io_core_1_resp_bits_data_MPORT_3_en = 1'h1;
  assign bytes_io_core_1_resp_bits_data_MPORT_3_addr = _io_core_1_resp_bits_data_T_9[20:0];
  assign bytes_io_core_1_resp_bits_data_MPORT_3_data = bytes[bytes_io_core_1_resp_bits_data_MPORT_3_addr];
  assign bytes_io_host_rdata_MPORT_en = 1'h1;
  assign bytes_io_host_rdata_MPORT_addr = io_host_rdata_base + 21'h3;
  assign bytes_io_host_rdata_MPORT_data = bytes[bytes_io_host_rdata_MPORT_addr];
  assign bytes_io_host_rdata_MPORT_1_en = 1'h1;
  assign bytes_io_host_rdata_MPORT_1_addr = io_host_rdata_base + 21'h2;
  assign bytes_io_host_rdata_MPORT_1_data = bytes[bytes_io_host_rdata_MPORT_1_addr];
  assign bytes_io_host_rdata_MPORT_2_en = 1'h1;
  assign bytes_io_host_rdata_MPORT_2_addr = io_host_rdata_base + 21'h1;
  assign bytes_io_host_rdata_MPORT_2_data = bytes[bytes_io_host_rdata_MPORT_2_addr];
  assign bytes_io_host_rdata_MPORT_3_en = 1'h1;
  assign bytes_io_host_rdata_MPORT_3_addr = _io_host_rdata_T_9[20:0];
  assign bytes_io_host_rdata_MPORT_3_data = bytes[bytes_io_host_rdata_MPORT_3_addr];
  assign bytes_io_tohost_MPORT_en = 1'h1;
  assign bytes_io_tohost_MPORT_addr = 21'h1003;
  assign bytes_io_tohost_MPORT_data = bytes[bytes_io_tohost_MPORT_addr];
  assign bytes_io_tohost_MPORT_1_en = 1'h1;
  assign bytes_io_tohost_MPORT_1_addr = 21'h1002;
  assign bytes_io_tohost_MPORT_1_data = bytes[bytes_io_tohost_MPORT_1_addr];
  assign bytes_io_tohost_MPORT_2_en = 1'h1;
  assign bytes_io_tohost_MPORT_2_addr = 21'h1001;
  assign bytes_io_tohost_MPORT_2_data = bytes[bytes_io_tohost_MPORT_2_addr];
  assign bytes_io_tohost_MPORT_3_en = 1'h1;
  assign bytes_io_tohost_MPORT_3_addr = 21'h1000;
  assign bytes_io_tohost_MPORT_3_data = bytes[bytes_io_tohost_MPORT_3_addr];
  assign bytes_MPORT_data = io_core_0_req_bits_data[7:0];
  assign bytes_MPORT_addr = _T_5[20:0];
  assign bytes_MPORT_mask = 1'h1;
  assign bytes_MPORT_en = io_core_0_req_valid & io_core_0_req_bits_fcn & ~io_host_valid & 3'h0 < storeBytes;
  assign bytes_MPORT_1_data = io_core_0_req_bits_data[15:8];
  assign bytes_MPORT_1_addr = _T_11[20:0];
  assign bytes_MPORT_1_mask = 1'h1;
  assign bytes_MPORT_1_en = io_core_0_req_valid & io_core_0_req_bits_fcn & ~io_host_valid & 3'h1 < storeBytes;
  assign bytes_MPORT_2_data = io_core_0_req_bits_data[23:16];
  assign bytes_MPORT_2_addr = _T_16[20:0];
  assign bytes_MPORT_2_mask = 1'h1;
  assign bytes_MPORT_2_en = io_core_0_req_valid & io_core_0_req_bits_fcn & ~io_host_valid & 3'h2 < storeBytes;
  assign bytes_MPORT_3_data = io_core_0_req_bits_data[31:24];
  assign bytes_MPORT_3_addr = _T_21[20:0];
  assign bytes_MPORT_3_mask = 1'h1;
  assign bytes_MPORT_3_en = io_core_0_req_valid & io_core_0_req_bits_fcn & ~io_host_valid & 3'h3 < storeBytes;
  assign bytes_MPORT_4_data = io_host_wdata[7:0];
  assign bytes_MPORT_4_addr = _T_25[20:0];
  assign bytes_MPORT_4_mask = 1'h1;
  assign bytes_MPORT_4_en = io_host_valid & io_host_write;
  assign bytes_MPORT_5_data = io_host_wdata[15:8];
  assign bytes_MPORT_5_addr = _T_30[20:0];
  assign bytes_MPORT_5_mask = 1'h1;
  assign bytes_MPORT_5_en = io_host_valid & io_host_write;
  assign bytes_MPORT_6_data = io_host_wdata[23:16];
  assign bytes_MPORT_6_addr = _T_34[20:0];
  assign bytes_MPORT_6_mask = 1'h1;
  assign bytes_MPORT_6_en = io_host_valid & io_host_write;
  assign bytes_MPORT_7_data = io_host_wdata[31:24];
  assign bytes_MPORT_7_addr = _T_38[20:0];
  assign bytes_MPORT_7_mask = 1'h1;
  assign bytes_MPORT_7_en = io_host_valid & io_host_write;
  assign io_core_0_resp_valid = io_core_0_req_valid;
  assign io_core_0_resp_bits_data = 3'h6 == io_core_0_req_bits_typ ? _io_core_0_resp_bits_data_T_13 :
    _io_core_0_resp_bits_data_T_19;
  assign io_core_1_resp_bits_data = {io_core_1_resp_bits_data_hi,io_core_1_resp_bits_data_lo};
  assign io_host_rdata = {io_host_rdata_hi,io_host_rdata_lo};
  assign io_tohost = {io_tohost_hi,io_tohost_lo};
  always @(posedge clock) begin
    if (bytes_MPORT_en & bytes_MPORT_mask) begin
      bytes[bytes_MPORT_addr] <= bytes_MPORT_data;
    end
    if (bytes_MPORT_1_en & bytes_MPORT_1_mask) begin
      bytes[bytes_MPORT_1_addr] <= bytes_MPORT_1_data;
    end
    if (bytes_MPORT_2_en & bytes_MPORT_2_mask) begin
      bytes[bytes_MPORT_2_addr] <= bytes_MPORT_2_data;
    end
    if (bytes_MPORT_3_en & bytes_MPORT_3_mask) begin
      bytes[bytes_MPORT_3_addr] <= bytes_MPORT_3_data;
    end
    if (bytes_MPORT_4_en & bytes_MPORT_4_mask) begin
      bytes[bytes_MPORT_4_addr] <= bytes_MPORT_4_data;
    end
    if (bytes_MPORT_5_en & bytes_MPORT_5_mask) begin
      bytes[bytes_MPORT_5_addr] <= bytes_MPORT_5_data;
    end
    if (bytes_MPORT_6_en & bytes_MPORT_6_mask) begin
      bytes[bytes_MPORT_6_addr] <= bytes_MPORT_6_data;
    end
    if (bytes_MPORT_7_en & bytes_MPORT_7_mask) begin
      bytes[bytes_MPORT_7_addr] <= bytes_MPORT_7_data;
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_MEM_INIT
  _RAND_0 = {1{`RANDOM}};
  for (initvar = 0; initvar < 2097152; initvar = initvar+1)
    bytes[initvar] = _RAND_0[7:0];
`endif // RANDOMIZE_MEM_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module RegisterFile(
  input         clock,
  input  [4:0]  io_rs1_addr,
  output [31:0] io_rs1_data,
  input  [4:0]  io_rs2_addr,
  output [31:0] io_rs2_data,
  input  [4:0]  io_waddr,
  input  [31:0] io_wdata,
  input         io_wen
);
`ifdef RANDOMIZE_MEM_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_MEM_INIT
  reg [31:0] regfile [0:31];
  wire  regfile_io_rs1_data_MPORT_en;
  wire [4:0] regfile_io_rs1_data_MPORT_addr;
  wire [31:0] regfile_io_rs1_data_MPORT_data;
  wire  regfile_io_rs2_data_MPORT_en;
  wire [4:0] regfile_io_rs2_data_MPORT_addr;
  wire [31:0] regfile_io_rs2_data_MPORT_data;
  wire  regfile_io_dm_rdata_MPORT_en;
  wire [4:0] regfile_io_dm_rdata_MPORT_addr;
  wire [31:0] regfile_io_dm_rdata_MPORT_data;
  wire [31:0] regfile_MPORT_data;
  wire [4:0] regfile_MPORT_addr;
  wire  regfile_MPORT_mask;
  wire  regfile_MPORT_en;
  wire [31:0] regfile_MPORT_1_data;
  wire [4:0] regfile_MPORT_1_addr;
  wire  regfile_MPORT_1_mask;
  wire  regfile_MPORT_1_en;
  assign regfile_io_rs1_data_MPORT_en = 1'h1;
  assign regfile_io_rs1_data_MPORT_addr = io_rs1_addr;
  assign regfile_io_rs1_data_MPORT_data = regfile[regfile_io_rs1_data_MPORT_addr];
  assign regfile_io_rs2_data_MPORT_en = 1'h1;
  assign regfile_io_rs2_data_MPORT_addr = io_rs2_addr;
  assign regfile_io_rs2_data_MPORT_data = regfile[regfile_io_rs2_data_MPORT_addr];
  assign regfile_io_dm_rdata_MPORT_en = 1'h1;
  assign regfile_io_dm_rdata_MPORT_addr = 5'h0;
  assign regfile_io_dm_rdata_MPORT_data = regfile[regfile_io_dm_rdata_MPORT_addr];
  assign regfile_MPORT_data = io_wdata;
  assign regfile_MPORT_addr = io_waddr;
  assign regfile_MPORT_mask = 1'h1;
  assign regfile_MPORT_en = io_wen & io_waddr != 5'h0;
  assign regfile_MPORT_1_data = 32'h0;
  assign regfile_MPORT_1_addr = 5'h0;
  assign regfile_MPORT_1_mask = 1'h1;
  assign regfile_MPORT_1_en = 1'h0;
  assign io_rs1_data = io_rs1_addr != 5'h0 ? regfile_io_rs1_data_MPORT_data : 32'h0;
  assign io_rs2_data = io_rs2_addr != 5'h0 ? regfile_io_rs2_data_MPORT_data : 32'h0;
  always @(posedge clock) begin
    if (regfile_MPORT_en & regfile_MPORT_mask) begin
      regfile[regfile_MPORT_addr] <= regfile_MPORT_data;
    end
    if (regfile_MPORT_1_en & regfile_MPORT_1_mask) begin
      regfile[regfile_MPORT_1_addr] <= regfile_MPORT_1_data;
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_MEM_INIT
  _RAND_0 = {1{`RANDOM}};
  for (initvar = 0; initvar < 32; initvar = initvar+1)
    regfile[initvar] = _RAND_0[31:0];
`endif // RANDOMIZE_MEM_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module SodorFullChip(
  input         clock,
  input         reset,
  input         io_host_valid,
  input         io_host_write,
  input  [31:0] io_host_addr,
  input  [31:0] io_host_wdata,
  output        io_host_ready,
  output [31:0] io_host_rdata,
  output        io_success,
  output [31:0] io_tohost
);
  wire  tile_clock;
  wire  tile_reset;
  wire [31:0] tile_io_imem_req_bits_addr;
  wire [31:0] tile_io_imem_resp_bits_data;
  wire  tile_io_dmem_req_valid;
  wire [31:0] tile_io_dmem_req_bits_addr;
  wire [31:0] tile_io_dmem_req_bits_data;
  wire  tile_io_dmem_req_bits_fcn;
  wire [2:0] tile_io_dmem_req_bits_typ;
  wire  tile_io_dmem_resp_valid;
  wire [31:0] tile_io_dmem_resp_bits_data;
  wire [4:0] tile_io_rf_read_rs1_addr;
  wire [31:0] tile_io_rf_read_rs1_data;
  wire [4:0] tile_io_rf_read_rs2_addr;
  wire [31:0] tile_io_rf_read_rs2_data;
  wire [4:0] tile_io_rf_write_waddr;
  wire [31:0] tile_io_rf_write_wdata;
  wire  tile_io_rf_write_wen;
  wire  memory_clock;
  wire  memory_io_core_0_req_valid;
  wire [31:0] memory_io_core_0_req_bits_addr;
  wire [31:0] memory_io_core_0_req_bits_data;
  wire  memory_io_core_0_req_bits_fcn;
  wire [2:0] memory_io_core_0_req_bits_typ;
  wire  memory_io_core_0_resp_valid;
  wire [31:0] memory_io_core_0_resp_bits_data;
  wire [31:0] memory_io_core_1_req_bits_addr;
  wire [31:0] memory_io_core_1_resp_bits_data;
  wire  memory_io_host_valid;
  wire  memory_io_host_write;
  wire [31:0] memory_io_host_addr;
  wire [31:0] memory_io_host_wdata;
  wire [31:0] memory_io_host_rdata;
  wire [31:0] memory_io_tohost;
  wire  regfile_clock;
  wire [4:0] regfile_io_rs1_addr;
  wire [31:0] regfile_io_rs1_data;
  wire [4:0] regfile_io_rs2_addr;
  wire [31:0] regfile_io_rs2_data;
  wire [4:0] regfile_io_waddr;
  wire [31:0] regfile_io_wdata;
  wire  regfile_io_wen;
  SodorTile tile (
    .clock(tile_clock),
    .reset(tile_reset),
    .io_imem_req_bits_addr(tile_io_imem_req_bits_addr),
    .io_imem_resp_bits_data(tile_io_imem_resp_bits_data),
    .io_dmem_req_valid(tile_io_dmem_req_valid),
    .io_dmem_req_bits_addr(tile_io_dmem_req_bits_addr),
    .io_dmem_req_bits_data(tile_io_dmem_req_bits_data),
    .io_dmem_req_bits_fcn(tile_io_dmem_req_bits_fcn),
    .io_dmem_req_bits_typ(tile_io_dmem_req_bits_typ),
    .io_dmem_resp_valid(tile_io_dmem_resp_valid),
    .io_dmem_resp_bits_data(tile_io_dmem_resp_bits_data),
    .io_rf_read_rs1_addr(tile_io_rf_read_rs1_addr),
    .io_rf_read_rs1_data(tile_io_rf_read_rs1_data),
    .io_rf_read_rs2_addr(tile_io_rf_read_rs2_addr),
    .io_rf_read_rs2_data(tile_io_rf_read_rs2_data),
    .io_rf_write_waddr(tile_io_rf_write_waddr),
    .io_rf_write_wdata(tile_io_rf_write_wdata),
    .io_rf_write_wen(tile_io_rf_write_wen)
  );
  SodorFullChipMemory memory (
    .clock(memory_clock),
    .io_core_0_req_valid(memory_io_core_0_req_valid),
    .io_core_0_req_bits_addr(memory_io_core_0_req_bits_addr),
    .io_core_0_req_bits_data(memory_io_core_0_req_bits_data),
    .io_core_0_req_bits_fcn(memory_io_core_0_req_bits_fcn),
    .io_core_0_req_bits_typ(memory_io_core_0_req_bits_typ),
    .io_core_0_resp_valid(memory_io_core_0_resp_valid),
    .io_core_0_resp_bits_data(memory_io_core_0_resp_bits_data),
    .io_core_1_req_bits_addr(memory_io_core_1_req_bits_addr),
    .io_core_1_resp_bits_data(memory_io_core_1_resp_bits_data),
    .io_host_valid(memory_io_host_valid),
    .io_host_write(memory_io_host_write),
    .io_host_addr(memory_io_host_addr),
    .io_host_wdata(memory_io_host_wdata),
    .io_host_rdata(memory_io_host_rdata),
    .io_tohost(memory_io_tohost)
  );
  RegisterFile regfile (
    .clock(regfile_clock),
    .io_rs1_addr(regfile_io_rs1_addr),
    .io_rs1_data(regfile_io_rs1_data),
    .io_rs2_addr(regfile_io_rs2_addr),
    .io_rs2_data(regfile_io_rs2_data),
    .io_waddr(regfile_io_waddr),
    .io_wdata(regfile_io_wdata),
    .io_wen(regfile_io_wen)
  );
  assign io_host_ready = 1'h1;
  assign io_host_rdata = memory_io_host_rdata;
  assign io_success = memory_io_tohost == 32'h1;
  assign io_tohost = memory_io_tohost;
  assign tile_clock = clock;
  assign tile_reset = reset;
  assign tile_io_imem_resp_bits_data = memory_io_core_1_resp_bits_data;
  assign tile_io_dmem_resp_valid = memory_io_core_0_resp_valid;
  assign tile_io_dmem_resp_bits_data = memory_io_core_0_resp_bits_data;
  assign tile_io_rf_read_rs1_data = regfile_io_rs1_data;
  assign tile_io_rf_read_rs2_data = regfile_io_rs2_data;
  assign memory_clock = clock;
  assign memory_io_core_0_req_valid = tile_io_dmem_req_valid;
  assign memory_io_core_0_req_bits_addr = tile_io_dmem_req_bits_addr;
  assign memory_io_core_0_req_bits_data = tile_io_dmem_req_bits_data;
  assign memory_io_core_0_req_bits_fcn = tile_io_dmem_req_bits_fcn;
  assign memory_io_core_0_req_bits_typ = tile_io_dmem_req_bits_typ;
  assign memory_io_core_1_req_bits_addr = tile_io_imem_req_bits_addr;
  assign memory_io_host_valid = io_host_valid;
  assign memory_io_host_write = io_host_write;
  assign memory_io_host_addr = io_host_addr;
  assign memory_io_host_wdata = io_host_wdata;
  assign regfile_clock = clock;
  assign regfile_io_rs1_addr = tile_io_rf_read_rs1_addr;
  assign regfile_io_rs2_addr = tile_io_rf_read_rs2_addr;
  assign regfile_io_waddr = tile_io_rf_write_waddr;
  assign regfile_io_wdata = tile_io_rf_write_wdata;
  assign regfile_io_wen = tile_io_rf_write_wen;
endmodule
