// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFeedForwardMatMul.h for the primary calling header

#include "VFeedForwardMatMul__pch.h"
#include "VFeedForwardMatMul___024root.h"

VL_INLINE_OPT void VFeedForwardMatMul___024root___ico_sequent__TOP__1(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___ico_sequent__TOP__1\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_1_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_1))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_17)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_33))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_49)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_65))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_81))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_97))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_113))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_129))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_145))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_161))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_177))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_193))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_209))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_225))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_241))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_2_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_2))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_18)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_34))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_50)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_66))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_82))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_98))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_114))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_130))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_146))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_162))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_178))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_194))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_210))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_226))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_242))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_3_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_3))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_19)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_35))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_51)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_67))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_83))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_99))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_115))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_131))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_147))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_163))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_179))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_195))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_211))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_227))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_243))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_4_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_4))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_20)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_36))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_52)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_68))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_84))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_100))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_116))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_132))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_148))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_164))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_180))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_196))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_212))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_228))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_244))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_5_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_5))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_21)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_37))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_53)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_69))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_85))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_101))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_117))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_133))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_149))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_165))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_181))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_197))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_213))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_229))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_245))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_6_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_6))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_22)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_38))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_54)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_70))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_86))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_102))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_118))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_134))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_150))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_166))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_182))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_198))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_214))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_230))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_246))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_7_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_7))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_23)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_39))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_55)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_71))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_87))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_103))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_119))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_135))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_151))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_167))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_183))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_199))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_215))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_231))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_247))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_8_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_8))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_24)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_40))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_56)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_72))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_88))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_104))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_120))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_136))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_152))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_168))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_184))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_200))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_216))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_232))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_248))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_9_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_9))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_25)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_41))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_57)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_73))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_89))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_105))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_121))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_137))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_153))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_169))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_185))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_201))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_217))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_233))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_249))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_10_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_10))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_26)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_42))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_58)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_74))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_90))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_106))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_122))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_138))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_154))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_170))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_186))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_202))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_218))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_234))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_250))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_11_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_11))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_27)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_43))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_59)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_75))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_91))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_107))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_123))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_139))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_155))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_171))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_187))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_203))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_219))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_235))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_251))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_12_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_12))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_28)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_44))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_60)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_76))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_92))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_108))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_124))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_140))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_156))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_172))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_188))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_204))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_220))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_236))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_252))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_13_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_13))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_29)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_45))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_61)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_77))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_93))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_109))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_125))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_141))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_157))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_173))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_189))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_205))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_221))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_237))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_253))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_14_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_14))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_30)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_46))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_62)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_78))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_94))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_110))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_126))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_142))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_158))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_174))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_190))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_206))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_222))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_238))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_254))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_15_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_176) 
                        * (IData)(vlSelfRef.in_b_15))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_177) 
                          * (IData)(vlSelfRef.in_b_31)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_178) 
                           * (IData)(vlSelfRef.in_b_47))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_179) 
                             * (IData)(vlSelfRef.in_b_63)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_180) 
                             * (IData)(vlSelfRef.in_b_79))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_181) 
                                 * (IData)(vlSelfRef.in_b_95))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_182) 
                                    * (IData)(vlSelfRef.in_b_111))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_183) 
                                      * (IData)(vlSelfRef.in_b_127))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_184) 
                                   * (IData)(vlSelfRef.in_b_143))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_185) 
                                      * (IData)(vlSelfRef.in_b_159))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_186) 
                                         * (IData)(vlSelfRef.in_b_175))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_187) 
                                            * (IData)(vlSelfRef.in_b_191))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_188) 
                                               * (IData)(vlSelfRef.in_b_207))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_189) 
                                                  * (IData)(vlSelfRef.in_b_223))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_190) 
                                           * (IData)(vlSelfRef.in_b_239))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_191) 
                                               * (IData)(vlSelfRef.in_b_255))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_0_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_0))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_16)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_32))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_48)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_64))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_80))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_96))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_112))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_128))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_144))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_160))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_176))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_192))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_208))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_224))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_240))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_1_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_1))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_17)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_33))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_49)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_65))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_81))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_97))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_113))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_129))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_145))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_161))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_177))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_193))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_209))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_225))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_241))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_2_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_2))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_18)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_34))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_50)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_66))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_82))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_98))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_114))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_130))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_146))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_162))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_178))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_194))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_210))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_226))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_242))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_3_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_3))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_19)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_35))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_51)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_67))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_83))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_99))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_115))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_131))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_147))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_163))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_179))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_195))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_211))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_227))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_243))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_4_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_4))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_20)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_36))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_52)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_68))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_84))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_100))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_116))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_132))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_148))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_164))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_180))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_196))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_212))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_228))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_244))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_5_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_5))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_21)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_37))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_53)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_69))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_85))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_101))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_117))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_133))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_149))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_165))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_181))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_197))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_213))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_229))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_245))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_6_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_6))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_22)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_38))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_54)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_70))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_86))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_102))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_118))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_134))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_150))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_166))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_182))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_198))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_214))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_230))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_246))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_7_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_7))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_23)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_39))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_55)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_71))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_87))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_103))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_119))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_135))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_151))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_167))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_183))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_199))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_215))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_231))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_247))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_8_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_8))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_24)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_40))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_56)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_72))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_88))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_104))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_120))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_136))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_152))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_168))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_184))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_200))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_216))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_232))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_248))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_9_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_9))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_25)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_41))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_57)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_73))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_89))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_105))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_121))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_137))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_153))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_169))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_185))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_201))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_217))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_233))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_249))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_10_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_10))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_26)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_42))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_58)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_74))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_90))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_106))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_122))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_138))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_154))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_170))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_186))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_202))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_218))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_234))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_250))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_11_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_11))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_27)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_43))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_59)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_75))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_91))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_107))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_123))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_139))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_155))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_171))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_187))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_203))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_219))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_235))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_251))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_12_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_12))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_28)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_44))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_60)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_76))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_92))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_108))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_124))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_140))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_156))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_172))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_188))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_204))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_220))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_236))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_252))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_13_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_13))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_29)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_45))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_61)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_77))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_93))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_109))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_125))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_141))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_157))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_173))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_189))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_205))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_221))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_237))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_253))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_14_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_14))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_30)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_46))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_62)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_78))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_94))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_110))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_126))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_142))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_158))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_174))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_190))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_206))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_222))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_238))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_254))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_15_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_192) 
                        * (IData)(vlSelfRef.in_b_15))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_193) 
                          * (IData)(vlSelfRef.in_b_31)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_194) 
                           * (IData)(vlSelfRef.in_b_47))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_195) 
                             * (IData)(vlSelfRef.in_b_63)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_196) 
                             * (IData)(vlSelfRef.in_b_79))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_197) 
                                 * (IData)(vlSelfRef.in_b_95))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_198) 
                                    * (IData)(vlSelfRef.in_b_111))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_199) 
                                      * (IData)(vlSelfRef.in_b_127))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_200) 
                                   * (IData)(vlSelfRef.in_b_143))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_201) 
                                      * (IData)(vlSelfRef.in_b_159))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_202) 
                                         * (IData)(vlSelfRef.in_b_175))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_203) 
                                            * (IData)(vlSelfRef.in_b_191))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_204) 
                                               * (IData)(vlSelfRef.in_b_207))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_205) 
                                                  * (IData)(vlSelfRef.in_b_223))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_206) 
                                           * (IData)(vlSelfRef.in_b_239))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_207) 
                                               * (IData)(vlSelfRef.in_b_255))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_0_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_0))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_16)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_32))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_48)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_64))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_80))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_96))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_112))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_128))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_144))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_160))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_176))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_192))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_208))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_224))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_240))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_1_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_1))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_17)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_33))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_49)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_65))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_81))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_97))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_113))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_129))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_145))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_161))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_177))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_193))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_209))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_225))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_241))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_2_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_2))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_18)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_34))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_50)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_66))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_82))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_98))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_114))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_130))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_146))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_162))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_178))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_194))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_210))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_226))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_242))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_3_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_3))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_19)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_35))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_51)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_67))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_83))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_99))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_115))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_131))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_147))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_163))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_179))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_195))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_211))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_227))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_243))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_4_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_4))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_20)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_36))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_52)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_68))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_84))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_100))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_116))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_132))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_148))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_164))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_180))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_196))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_212))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_228))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_244))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_5_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_5))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_21)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_37))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_53)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_69))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_85))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_101))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_117))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_133))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_149))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_165))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_181))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_197))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_213))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_229))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_245))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_6_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_6))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_22)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_38))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_54)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_70))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_86))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_102))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_118))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_134))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_150))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_166))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_182))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_198))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_214))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_230))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_246))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_7_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_7))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_23)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_39))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_55)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_71))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_87))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_103))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_119))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_135))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_151))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_167))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_183))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_199))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_215))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_231))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_247))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_8_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_8))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_24)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_40))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_56)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_72))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_88))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_104))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_120))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_136))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_152))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_168))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_184))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_200))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_216))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_232))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_248))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_9_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_9))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_25)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_41))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_57)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_73))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_89))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_105))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_121))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_137))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_153))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_169))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_185))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_201))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_217))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_233))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_249))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_10_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_10))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_26)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_42))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_58)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_74))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_90))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_106))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_122))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_138))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_154))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_170))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_186))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_202))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_218))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_234))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_250))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_11_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_11))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_27)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_43))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_59)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_75))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_91))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_107))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_123))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_139))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_155))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_171))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_187))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_203))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_219))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_235))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_251))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_12_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_12))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_28)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_44))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_60)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_76))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_92))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_108))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_124))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_140))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_156))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_172))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_188))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_204))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_220))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_236))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_252))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_13_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_13))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_29)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_45))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_61)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_77))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_93))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_109))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_125))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_141))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_157))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_173))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_189))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_205))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_221))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_237))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_253))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_14_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_14))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_30)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_46))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_62)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_78))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_94))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_110))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_126))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_142))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_158))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_174))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_190))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_206))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_222))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_238))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_254))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_15_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_208) 
                        * (IData)(vlSelfRef.in_b_15))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_209) 
                          * (IData)(vlSelfRef.in_b_31)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_210) 
                           * (IData)(vlSelfRef.in_b_47))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_211) 
                             * (IData)(vlSelfRef.in_b_63)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_212) 
                             * (IData)(vlSelfRef.in_b_79))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_213) 
                                 * (IData)(vlSelfRef.in_b_95))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_214) 
                                    * (IData)(vlSelfRef.in_b_111))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_215) 
                                      * (IData)(vlSelfRef.in_b_127))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_216) 
                                   * (IData)(vlSelfRef.in_b_143))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_217) 
                                      * (IData)(vlSelfRef.in_b_159))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_218) 
                                         * (IData)(vlSelfRef.in_b_175))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_219) 
                                            * (IData)(vlSelfRef.in_b_191))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_220) 
                                               * (IData)(vlSelfRef.in_b_207))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_221) 
                                                  * (IData)(vlSelfRef.in_b_223))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_222) 
                                           * (IData)(vlSelfRef.in_b_239))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_223) 
                                               * (IData)(vlSelfRef.in_b_255))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_0_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_0))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_16)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_32))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_48)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_64))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_80))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_96))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_112))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_128))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_144))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_160))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_176))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_192))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_208))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_224))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_240))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_1_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_1))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_17)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_33))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_49)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_65))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_81))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_97))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_113))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_129))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_145))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_161))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_177))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_193))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_209))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_225))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_241))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_2_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_2))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_18)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_34))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_50)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_66))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_82))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_98))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_114))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_130))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_146))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_162))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_178))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_194))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_210))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_226))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_242))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_3_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_3))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_19)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_35))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_51)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_67))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_83))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_99))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_115))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_131))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_147))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_163))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_179))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_195))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_211))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_227))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_243))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_4_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_4))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_20)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_36))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_52)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_68))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_84))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_100))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_116))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_132))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_148))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_164))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_180))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_196))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_212))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_228))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_244))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_5_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_5))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_21)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_37))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_53)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_69))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_85))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_101))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_117))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_133))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_149))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_165))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_181))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_197))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_213))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_229))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_245))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_6_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_6))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_22)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_38))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_54)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_70))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_86))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_102))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_118))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_134))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_150))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_166))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_182))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_198))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_214))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_230))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_246))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_7_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_7))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_23)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_39))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_55)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_71))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_87))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_103))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_119))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_135))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_151))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_167))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_183))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_199))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_215))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_231))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_247))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_8_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_8))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_24)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_40))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_56)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_72))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_88))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_104))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_120))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_136))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_152))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_168))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_184))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_200))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_216))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_232))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_248))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_9_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_9))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_25)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_41))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_57)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_73))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_89))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_105))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_121))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_137))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_153))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_169))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_185))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_201))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_217))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_233))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_249))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_10_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_10))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_26)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_42))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_58)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_74))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_90))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_106))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_122))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_138))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_154))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_170))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_186))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_202))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_218))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_234))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_250))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_11_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_11))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_27)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_43))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_59)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_75))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_91))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_107))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_123))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_139))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_155))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_171))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_187))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_203))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_219))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_235))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_251))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_12_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_12))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_28)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_44))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_60)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_76))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_92))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_108))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_124))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_140))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_156))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_172))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_188))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_204))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_220))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_236))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_252))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_13_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_13))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_29)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_45))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_61)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_77))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_93))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_109))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_125))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_141))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_157))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_173))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_189))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_205))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_221))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_237))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_253))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_14_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_14))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_30)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_46))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_62)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_78))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_94))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_110))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_126))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_142))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_158))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_174))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_190))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_206))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_222))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_238))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_254))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_15_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_224) 
                        * (IData)(vlSelfRef.in_b_15))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_225) 
                          * (IData)(vlSelfRef.in_b_31)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_226) 
                           * (IData)(vlSelfRef.in_b_47))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_227) 
                             * (IData)(vlSelfRef.in_b_63)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_228) 
                             * (IData)(vlSelfRef.in_b_79))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_229) 
                                 * (IData)(vlSelfRef.in_b_95))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_230) 
                                    * (IData)(vlSelfRef.in_b_111))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_231) 
                                      * (IData)(vlSelfRef.in_b_127))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_232) 
                                   * (IData)(vlSelfRef.in_b_143))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_233) 
                                      * (IData)(vlSelfRef.in_b_159))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_234) 
                                         * (IData)(vlSelfRef.in_b_175))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_235) 
                                            * (IData)(vlSelfRef.in_b_191))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_236) 
                                               * (IData)(vlSelfRef.in_b_207))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_237) 
                                                  * (IData)(vlSelfRef.in_b_223))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_238) 
                                           * (IData)(vlSelfRef.in_b_239))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_239) 
                                               * (IData)(vlSelfRef.in_b_255))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_0_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_0))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_16)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_32))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_48)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_64))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_80))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_96))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_112))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_128))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_144))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_160))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_176))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_192))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_208))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_224))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_240))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_1_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_1))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_17)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_33))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_49)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_65))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_81))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_97))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_113))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_129))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_145))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_161))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_177))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_193))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_209))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_225))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_241))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_2_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_2))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_18)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_34))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_50)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_66))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_82))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_98))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_114))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_130))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_146))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_162))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_178))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_194))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_210))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_226))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_242))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_3_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_3))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_19)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_35))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_51)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_67))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_83))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_99))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_115))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_131))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_147))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_163))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_179))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_195))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_211))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_227))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_243))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_4_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_4))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_20)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_36))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_52)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_68))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_84))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_100))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_116))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_132))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_148))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_164))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_180))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_196))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_212))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_228))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_244))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_5_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_5))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_21)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_37))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_53)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_69))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_85))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_101))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_117))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_133))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_149))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_165))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_181))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_197))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_213))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_229))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_245))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_6_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_6))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_22)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_38))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_54)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_70))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_86))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_102))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_118))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_134))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_150))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_166))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_182))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_198))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_214))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_230))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_246))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_7_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_7))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_23)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_39))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_55)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_71))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_87))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_103))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_119))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_135))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_151))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_167))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_183))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_199))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_215))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_231))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_247))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_8_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_8))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_24)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_40))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_56)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_72))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_88))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_104))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_120))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_136))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_152))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_168))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_184))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_200))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_216))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_232))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_248))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_9_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_9))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_25)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_41))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_57)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_73))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_89))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_105))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_121))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_137))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_153))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_169))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_185))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_201))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_217))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_233))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_249))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_10_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_10))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_26)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_42))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_58)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_74))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_90))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_106))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_122))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_138))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_154))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_170))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_186))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_202))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_218))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_234))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_250))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_11_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_11))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_27)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_43))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_59)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_75))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_91))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_107))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_123))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_139))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_155))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_171))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_187))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_203))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_219))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_235))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_251))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_12_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_12))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_28)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_44))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_60)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_76))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_92))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_108))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_124))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_140))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_156))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_172))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_188))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_204))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_220))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_236))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_252))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_13_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_13))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_29)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_45))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_61)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_77))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_93))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_109))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_125))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_141))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_157))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_173))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_189))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_205))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_221))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_237))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_253))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_14_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_14))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_30)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_46))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_62)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_78))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_94))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_110))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_126))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_142))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_158))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_174))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_190))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_206))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_222))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_238))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_254))))))))))))));
    vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_15_0 
        = (((0xffffU & ((IData)(vlSelfRef.in_a_240) 
                        * (IData)(vlSelfRef.in_b_15))) 
            + (0xffffU & ((IData)(vlSelfRef.in_a_241) 
                          * (IData)(vlSelfRef.in_b_31)))) 
           + (((0xffffU & ((IData)(vlSelfRef.in_a_242) 
                           * (IData)(vlSelfRef.in_b_47))) 
               + (0xffffU & ((IData)(vlSelfRef.in_a_243) 
                             * (IData)(vlSelfRef.in_b_63)))) 
              + ((0xffffU & ((IData)(vlSelfRef.in_a_244) 
                             * (IData)(vlSelfRef.in_b_79))) 
                 + (((0xffffU & ((IData)(vlSelfRef.in_a_245) 
                                 * (IData)(vlSelfRef.in_b_95))) 
                     + ((0xffffU & ((IData)(vlSelfRef.in_a_246) 
                                    * (IData)(vlSelfRef.in_b_111))) 
                        + (0xffffU & ((IData)(vlSelfRef.in_a_247) 
                                      * (IData)(vlSelfRef.in_b_127))))) 
                    + ((0xffffU & ((IData)(vlSelfRef.in_a_248) 
                                   * (IData)(vlSelfRef.in_b_143))) 
                       + ((0xffffU & ((IData)(vlSelfRef.in_a_249) 
                                      * (IData)(vlSelfRef.in_b_159))) 
                          + ((0xffffU & ((IData)(vlSelfRef.in_a_250) 
                                         * (IData)(vlSelfRef.in_b_175))) 
                             + ((0xffffU & ((IData)(vlSelfRef.in_a_251) 
                                            * (IData)(vlSelfRef.in_b_191))) 
                                + ((0xffffU & ((IData)(vlSelfRef.in_a_252) 
                                               * (IData)(vlSelfRef.in_b_207))) 
                                   + ((0xffffU & ((IData)(vlSelfRef.in_a_253) 
                                                  * (IData)(vlSelfRef.in_b_223))) 
                                      + ((0xffffU & 
                                          ((IData)(vlSelfRef.in_a_254) 
                                           * (IData)(vlSelfRef.in_b_239))) 
                                         + (0xffffU 
                                            & ((IData)(vlSelfRef.in_a_255) 
                                               * (IData)(vlSelfRef.in_b_255))))))))))))));
}

void VFeedForwardMatMul___024root___eval_triggers__ico(VFeedForwardMatMul___024root* vlSelf);
void VFeedForwardMatMul___024root___eval_ico(VFeedForwardMatMul___024root* vlSelf);

bool VFeedForwardMatMul___024root___eval_phase__ico(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_phase__ico\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VFeedForwardMatMul___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VFeedForwardMatMul___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VFeedForwardMatMul___024root___eval_act(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_act\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__0(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root___eval_nba(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_nba\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VFeedForwardMatMul___024root___nba_sequent__TOP__0(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___nba_sequent__TOP__0\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.reset) {
        vlSelfRef.FeedForwardMatMul__DOT__result_7_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_15 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_0 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_1 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_2 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_3 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_4 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_5 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_6 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_7 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_8 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_9 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_10 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_11 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_12 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_13 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_14 = 0U;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_15 = 0U;
    } else {
        vlSelfRef.FeedForwardMatMul__DOT__result_7_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_6_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_6_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_4_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_4_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_5_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_5_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_0_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_0_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_1_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_1_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_2_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_2_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_3_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_3_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_7_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_7_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_8_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_8_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_9_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_9_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_10_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_10_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_11_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_11_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_12_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_12_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_13_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_13_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_14_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_14_15_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_0 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_0_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_1 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_1_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_2 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_2_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_3 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_3_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_4 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_4_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_5 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_5_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_6 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_6_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_7 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_7_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_8 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_8_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_9 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_9_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_10 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_10_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_11 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_11_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_12 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_12_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_13 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_13_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_14 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_14_0;
        vlSelfRef.FeedForwardMatMul__DOT__result_15_15 
            = vlSelfRef.FeedForwardMatMul__DOT__sum_3_15_15_0;
    }
    vlSelfRef.out_126 = vlSelfRef.FeedForwardMatMul__DOT__result_7_14;
    vlSelfRef.out_125 = vlSelfRef.FeedForwardMatMul__DOT__result_7_13;
    vlSelfRef.out_124 = vlSelfRef.FeedForwardMatMul__DOT__result_7_12;
    vlSelfRef.out_123 = vlSelfRef.FeedForwardMatMul__DOT__result_7_11;
    vlSelfRef.out_122 = vlSelfRef.FeedForwardMatMul__DOT__result_7_10;
    vlSelfRef.out_121 = vlSelfRef.FeedForwardMatMul__DOT__result_7_9;
    vlSelfRef.out_120 = vlSelfRef.FeedForwardMatMul__DOT__result_7_8;
    vlSelfRef.out_119 = vlSelfRef.FeedForwardMatMul__DOT__result_7_7;
    vlSelfRef.out_118 = vlSelfRef.FeedForwardMatMul__DOT__result_7_6;
    vlSelfRef.out_117 = vlSelfRef.FeedForwardMatMul__DOT__result_7_5;
    vlSelfRef.out_116 = vlSelfRef.FeedForwardMatMul__DOT__result_7_4;
    vlSelfRef.out_115 = vlSelfRef.FeedForwardMatMul__DOT__result_7_3;
    vlSelfRef.out_114 = vlSelfRef.FeedForwardMatMul__DOT__result_7_2;
    vlSelfRef.out_113 = vlSelfRef.FeedForwardMatMul__DOT__result_7_1;
    vlSelfRef.out_112 = vlSelfRef.FeedForwardMatMul__DOT__result_7_0;
    vlSelfRef.out_111 = vlSelfRef.FeedForwardMatMul__DOT__result_6_15;
    vlSelfRef.out_110 = vlSelfRef.FeedForwardMatMul__DOT__result_6_14;
    vlSelfRef.out_109 = vlSelfRef.FeedForwardMatMul__DOT__result_6_13;
    vlSelfRef.out_108 = vlSelfRef.FeedForwardMatMul__DOT__result_6_12;
    vlSelfRef.out_107 = vlSelfRef.FeedForwardMatMul__DOT__result_6_11;
    vlSelfRef.out_106 = vlSelfRef.FeedForwardMatMul__DOT__result_6_10;
    vlSelfRef.out_105 = vlSelfRef.FeedForwardMatMul__DOT__result_6_9;
    vlSelfRef.out_104 = vlSelfRef.FeedForwardMatMul__DOT__result_6_8;
    vlSelfRef.out_103 = vlSelfRef.FeedForwardMatMul__DOT__result_6_7;
    vlSelfRef.out_102 = vlSelfRef.FeedForwardMatMul__DOT__result_6_6;
    vlSelfRef.out_101 = vlSelfRef.FeedForwardMatMul__DOT__result_6_5;
    vlSelfRef.out_100 = vlSelfRef.FeedForwardMatMul__DOT__result_6_4;
    vlSelfRef.out_99 = vlSelfRef.FeedForwardMatMul__DOT__result_6_3;
    vlSelfRef.out_98 = vlSelfRef.FeedForwardMatMul__DOT__result_6_2;
    vlSelfRef.out_97 = vlSelfRef.FeedForwardMatMul__DOT__result_6_1;
    vlSelfRef.out_96 = vlSelfRef.FeedForwardMatMul__DOT__result_6_0;
    vlSelfRef.out_94 = vlSelfRef.FeedForwardMatMul__DOT__result_5_14;
    vlSelfRef.out_93 = vlSelfRef.FeedForwardMatMul__DOT__result_5_13;
    vlSelfRef.out_92 = vlSelfRef.FeedForwardMatMul__DOT__result_5_12;
    vlSelfRef.out_91 = vlSelfRef.FeedForwardMatMul__DOT__result_5_11;
    vlSelfRef.out_90 = vlSelfRef.FeedForwardMatMul__DOT__result_5_10;
    vlSelfRef.out_89 = vlSelfRef.FeedForwardMatMul__DOT__result_5_9;
    vlSelfRef.out_88 = vlSelfRef.FeedForwardMatMul__DOT__result_5_8;
    vlSelfRef.out_87 = vlSelfRef.FeedForwardMatMul__DOT__result_5_7;
    vlSelfRef.out_86 = vlSelfRef.FeedForwardMatMul__DOT__result_5_6;
    vlSelfRef.out_85 = vlSelfRef.FeedForwardMatMul__DOT__result_5_5;
    vlSelfRef.out_84 = vlSelfRef.FeedForwardMatMul__DOT__result_5_4;
    vlSelfRef.out_83 = vlSelfRef.FeedForwardMatMul__DOT__result_5_3;
    vlSelfRef.out_82 = vlSelfRef.FeedForwardMatMul__DOT__result_5_2;
    vlSelfRef.out_81 = vlSelfRef.FeedForwardMatMul__DOT__result_5_1;
    vlSelfRef.out_80 = vlSelfRef.FeedForwardMatMul__DOT__result_5_0;
    vlSelfRef.out_79 = vlSelfRef.FeedForwardMatMul__DOT__result_4_15;
    vlSelfRef.out_78 = vlSelfRef.FeedForwardMatMul__DOT__result_4_14;
    vlSelfRef.out_77 = vlSelfRef.FeedForwardMatMul__DOT__result_4_13;
    vlSelfRef.out_76 = vlSelfRef.FeedForwardMatMul__DOT__result_4_12;
    vlSelfRef.out_75 = vlSelfRef.FeedForwardMatMul__DOT__result_4_11;
    vlSelfRef.out_74 = vlSelfRef.FeedForwardMatMul__DOT__result_4_10;
    vlSelfRef.out_73 = vlSelfRef.FeedForwardMatMul__DOT__result_4_9;
    vlSelfRef.out_72 = vlSelfRef.FeedForwardMatMul__DOT__result_4_8;
    vlSelfRef.out_71 = vlSelfRef.FeedForwardMatMul__DOT__result_4_7;
    vlSelfRef.out_70 = vlSelfRef.FeedForwardMatMul__DOT__result_4_6;
    vlSelfRef.out_69 = vlSelfRef.FeedForwardMatMul__DOT__result_4_5;
    vlSelfRef.out_68 = vlSelfRef.FeedForwardMatMul__DOT__result_4_4;
    vlSelfRef.out_67 = vlSelfRef.FeedForwardMatMul__DOT__result_4_3;
    vlSelfRef.out_66 = vlSelfRef.FeedForwardMatMul__DOT__result_4_2;
    vlSelfRef.out_65 = vlSelfRef.FeedForwardMatMul__DOT__result_4_1;
    vlSelfRef.out_64 = vlSelfRef.FeedForwardMatMul__DOT__result_4_0;
    vlSelfRef.out_0 = vlSelfRef.FeedForwardMatMul__DOT__result_0_0;
    vlSelfRef.out_63 = vlSelfRef.FeedForwardMatMul__DOT__result_3_15;
    vlSelfRef.out_62 = vlSelfRef.FeedForwardMatMul__DOT__result_3_14;
    vlSelfRef.out_61 = vlSelfRef.FeedForwardMatMul__DOT__result_3_13;
    vlSelfRef.out_60 = vlSelfRef.FeedForwardMatMul__DOT__result_3_12;
    vlSelfRef.out_59 = vlSelfRef.FeedForwardMatMul__DOT__result_3_11;
    vlSelfRef.out_28 = vlSelfRef.FeedForwardMatMul__DOT__result_1_12;
    vlSelfRef.out_27 = vlSelfRef.FeedForwardMatMul__DOT__result_1_11;
    vlSelfRef.out_26 = vlSelfRef.FeedForwardMatMul__DOT__result_1_10;
    vlSelfRef.out_25 = vlSelfRef.FeedForwardMatMul__DOT__result_1_9;
    vlSelfRef.out_24 = vlSelfRef.FeedForwardMatMul__DOT__result_1_8;
    vlSelfRef.out_23 = vlSelfRef.FeedForwardMatMul__DOT__result_1_7;
    vlSelfRef.out_22 = vlSelfRef.FeedForwardMatMul__DOT__result_1_6;
    vlSelfRef.out_21 = vlSelfRef.FeedForwardMatMul__DOT__result_1_5;
    vlSelfRef.out_20 = vlSelfRef.FeedForwardMatMul__DOT__result_1_4;
    vlSelfRef.out_19 = vlSelfRef.FeedForwardMatMul__DOT__result_1_3;
    vlSelfRef.out_18 = vlSelfRef.FeedForwardMatMul__DOT__result_1_2;
    vlSelfRef.out_17 = vlSelfRef.FeedForwardMatMul__DOT__result_1_1;
    vlSelfRef.out_16 = vlSelfRef.FeedForwardMatMul__DOT__result_1_0;
    vlSelfRef.out_15 = vlSelfRef.FeedForwardMatMul__DOT__result_0_15;
    vlSelfRef.out_14 = vlSelfRef.FeedForwardMatMul__DOT__result_0_14;
    vlSelfRef.out_13 = vlSelfRef.FeedForwardMatMul__DOT__result_0_13;
    vlSelfRef.out_3 = vlSelfRef.FeedForwardMatMul__DOT__result_0_3;
    vlSelfRef.out_1 = vlSelfRef.FeedForwardMatMul__DOT__result_0_1;
    vlSelfRef.out_2 = vlSelfRef.FeedForwardMatMul__DOT__result_0_2;
    vlSelfRef.out_4 = vlSelfRef.FeedForwardMatMul__DOT__result_0_4;
    vlSelfRef.out_5 = vlSelfRef.FeedForwardMatMul__DOT__result_0_5;
    vlSelfRef.out_6 = vlSelfRef.FeedForwardMatMul__DOT__result_0_6;
    vlSelfRef.out_95 = vlSelfRef.FeedForwardMatMul__DOT__result_5_15;
    vlSelfRef.out_44 = vlSelfRef.FeedForwardMatMul__DOT__result_2_12;
    vlSelfRef.out_7 = vlSelfRef.FeedForwardMatMul__DOT__result_0_7;
    vlSelfRef.out_8 = vlSelfRef.FeedForwardMatMul__DOT__result_0_8;
    vlSelfRef.out_9 = vlSelfRef.FeedForwardMatMul__DOT__result_0_9;
    vlSelfRef.out_10 = vlSelfRef.FeedForwardMatMul__DOT__result_0_10;
    vlSelfRef.out_11 = vlSelfRef.FeedForwardMatMul__DOT__result_0_11;
    vlSelfRef.out_12 = vlSelfRef.FeedForwardMatMul__DOT__result_0_12;
    vlSelfRef.out_29 = vlSelfRef.FeedForwardMatMul__DOT__result_1_13;
    vlSelfRef.out_30 = vlSelfRef.FeedForwardMatMul__DOT__result_1_14;
    vlSelfRef.out_31 = vlSelfRef.FeedForwardMatMul__DOT__result_1_15;
    vlSelfRef.out_32 = vlSelfRef.FeedForwardMatMul__DOT__result_2_0;
    vlSelfRef.out_33 = vlSelfRef.FeedForwardMatMul__DOT__result_2_1;
    vlSelfRef.out_34 = vlSelfRef.FeedForwardMatMul__DOT__result_2_2;
    vlSelfRef.out_35 = vlSelfRef.FeedForwardMatMul__DOT__result_2_3;
    vlSelfRef.out_36 = vlSelfRef.FeedForwardMatMul__DOT__result_2_4;
    vlSelfRef.out_37 = vlSelfRef.FeedForwardMatMul__DOT__result_2_5;
    vlSelfRef.out_38 = vlSelfRef.FeedForwardMatMul__DOT__result_2_6;
    vlSelfRef.out_39 = vlSelfRef.FeedForwardMatMul__DOT__result_2_7;
    vlSelfRef.out_40 = vlSelfRef.FeedForwardMatMul__DOT__result_2_8;
    vlSelfRef.out_41 = vlSelfRef.FeedForwardMatMul__DOT__result_2_9;
    vlSelfRef.out_42 = vlSelfRef.FeedForwardMatMul__DOT__result_2_10;
    vlSelfRef.out_43 = vlSelfRef.FeedForwardMatMul__DOT__result_2_11;
    vlSelfRef.out_45 = vlSelfRef.FeedForwardMatMul__DOT__result_2_13;
    vlSelfRef.out_46 = vlSelfRef.FeedForwardMatMul__DOT__result_2_14;
    vlSelfRef.out_47 = vlSelfRef.FeedForwardMatMul__DOT__result_2_15;
    vlSelfRef.out_48 = vlSelfRef.FeedForwardMatMul__DOT__result_3_0;
    vlSelfRef.out_49 = vlSelfRef.FeedForwardMatMul__DOT__result_3_1;
    vlSelfRef.out_50 = vlSelfRef.FeedForwardMatMul__DOT__result_3_2;
    vlSelfRef.out_51 = vlSelfRef.FeedForwardMatMul__DOT__result_3_3;
    vlSelfRef.out_52 = vlSelfRef.FeedForwardMatMul__DOT__result_3_4;
    vlSelfRef.out_53 = vlSelfRef.FeedForwardMatMul__DOT__result_3_5;
    vlSelfRef.out_54 = vlSelfRef.FeedForwardMatMul__DOT__result_3_6;
    vlSelfRef.out_55 = vlSelfRef.FeedForwardMatMul__DOT__result_3_7;
    vlSelfRef.out_56 = vlSelfRef.FeedForwardMatMul__DOT__result_3_8;
    vlSelfRef.out_57 = vlSelfRef.FeedForwardMatMul__DOT__result_3_9;
    vlSelfRef.out_58 = vlSelfRef.FeedForwardMatMul__DOT__result_3_10;
    vlSelfRef.out_127 = vlSelfRef.FeedForwardMatMul__DOT__result_7_15;
    vlSelfRef.out_128 = vlSelfRef.FeedForwardMatMul__DOT__result_8_0;
    vlSelfRef.out_129 = vlSelfRef.FeedForwardMatMul__DOT__result_8_1;
    vlSelfRef.out_130 = vlSelfRef.FeedForwardMatMul__DOT__result_8_2;
    vlSelfRef.out_131 = vlSelfRef.FeedForwardMatMul__DOT__result_8_3;
    vlSelfRef.out_132 = vlSelfRef.FeedForwardMatMul__DOT__result_8_4;
    vlSelfRef.out_133 = vlSelfRef.FeedForwardMatMul__DOT__result_8_5;
    vlSelfRef.out_134 = vlSelfRef.FeedForwardMatMul__DOT__result_8_6;
    vlSelfRef.out_135 = vlSelfRef.FeedForwardMatMul__DOT__result_8_7;
    vlSelfRef.out_136 = vlSelfRef.FeedForwardMatMul__DOT__result_8_8;
    vlSelfRef.out_137 = vlSelfRef.FeedForwardMatMul__DOT__result_8_9;
    vlSelfRef.out_138 = vlSelfRef.FeedForwardMatMul__DOT__result_8_10;
    vlSelfRef.out_139 = vlSelfRef.FeedForwardMatMul__DOT__result_8_11;
    vlSelfRef.out_140 = vlSelfRef.FeedForwardMatMul__DOT__result_8_12;
    vlSelfRef.out_141 = vlSelfRef.FeedForwardMatMul__DOT__result_8_13;
    vlSelfRef.out_142 = vlSelfRef.FeedForwardMatMul__DOT__result_8_14;
    vlSelfRef.out_143 = vlSelfRef.FeedForwardMatMul__DOT__result_8_15;
    vlSelfRef.out_144 = vlSelfRef.FeedForwardMatMul__DOT__result_9_0;
    vlSelfRef.out_145 = vlSelfRef.FeedForwardMatMul__DOT__result_9_1;
    vlSelfRef.out_146 = vlSelfRef.FeedForwardMatMul__DOT__result_9_2;
    vlSelfRef.out_147 = vlSelfRef.FeedForwardMatMul__DOT__result_9_3;
    vlSelfRef.out_148 = vlSelfRef.FeedForwardMatMul__DOT__result_9_4;
    vlSelfRef.out_149 = vlSelfRef.FeedForwardMatMul__DOT__result_9_5;
    vlSelfRef.out_150 = vlSelfRef.FeedForwardMatMul__DOT__result_9_6;
    vlSelfRef.out_151 = vlSelfRef.FeedForwardMatMul__DOT__result_9_7;
    vlSelfRef.out_152 = vlSelfRef.FeedForwardMatMul__DOT__result_9_8;
    vlSelfRef.out_153 = vlSelfRef.FeedForwardMatMul__DOT__result_9_9;
    vlSelfRef.out_154 = vlSelfRef.FeedForwardMatMul__DOT__result_9_10;
    vlSelfRef.out_155 = vlSelfRef.FeedForwardMatMul__DOT__result_9_11;
    vlSelfRef.out_156 = vlSelfRef.FeedForwardMatMul__DOT__result_9_12;
    vlSelfRef.out_157 = vlSelfRef.FeedForwardMatMul__DOT__result_9_13;
    vlSelfRef.out_158 = vlSelfRef.FeedForwardMatMul__DOT__result_9_14;
    vlSelfRef.out_159 = vlSelfRef.FeedForwardMatMul__DOT__result_9_15;
    vlSelfRef.out_160 = vlSelfRef.FeedForwardMatMul__DOT__result_10_0;
    vlSelfRef.out_161 = vlSelfRef.FeedForwardMatMul__DOT__result_10_1;
    vlSelfRef.out_162 = vlSelfRef.FeedForwardMatMul__DOT__result_10_2;
    vlSelfRef.out_163 = vlSelfRef.FeedForwardMatMul__DOT__result_10_3;
    vlSelfRef.out_164 = vlSelfRef.FeedForwardMatMul__DOT__result_10_4;
    vlSelfRef.out_165 = vlSelfRef.FeedForwardMatMul__DOT__result_10_5;
    vlSelfRef.out_166 = vlSelfRef.FeedForwardMatMul__DOT__result_10_6;
    vlSelfRef.out_167 = vlSelfRef.FeedForwardMatMul__DOT__result_10_7;
    vlSelfRef.out_168 = vlSelfRef.FeedForwardMatMul__DOT__result_10_8;
    vlSelfRef.out_169 = vlSelfRef.FeedForwardMatMul__DOT__result_10_9;
    vlSelfRef.out_170 = vlSelfRef.FeedForwardMatMul__DOT__result_10_10;
    vlSelfRef.out_171 = vlSelfRef.FeedForwardMatMul__DOT__result_10_11;
    vlSelfRef.out_172 = vlSelfRef.FeedForwardMatMul__DOT__result_10_12;
    vlSelfRef.out_173 = vlSelfRef.FeedForwardMatMul__DOT__result_10_13;
    vlSelfRef.out_174 = vlSelfRef.FeedForwardMatMul__DOT__result_10_14;
    vlSelfRef.out_175 = vlSelfRef.FeedForwardMatMul__DOT__result_10_15;
    vlSelfRef.out_176 = vlSelfRef.FeedForwardMatMul__DOT__result_11_0;
    vlSelfRef.out_177 = vlSelfRef.FeedForwardMatMul__DOT__result_11_1;
    vlSelfRef.out_178 = vlSelfRef.FeedForwardMatMul__DOT__result_11_2;
    vlSelfRef.out_179 = vlSelfRef.FeedForwardMatMul__DOT__result_11_3;
    vlSelfRef.out_180 = vlSelfRef.FeedForwardMatMul__DOT__result_11_4;
    vlSelfRef.out_181 = vlSelfRef.FeedForwardMatMul__DOT__result_11_5;
    vlSelfRef.out_182 = vlSelfRef.FeedForwardMatMul__DOT__result_11_6;
    vlSelfRef.out_183 = vlSelfRef.FeedForwardMatMul__DOT__result_11_7;
    vlSelfRef.out_184 = vlSelfRef.FeedForwardMatMul__DOT__result_11_8;
    vlSelfRef.out_185 = vlSelfRef.FeedForwardMatMul__DOT__result_11_9;
    vlSelfRef.out_186 = vlSelfRef.FeedForwardMatMul__DOT__result_11_10;
    vlSelfRef.out_187 = vlSelfRef.FeedForwardMatMul__DOT__result_11_11;
    vlSelfRef.out_188 = vlSelfRef.FeedForwardMatMul__DOT__result_11_12;
    vlSelfRef.out_189 = vlSelfRef.FeedForwardMatMul__DOT__result_11_13;
    vlSelfRef.out_190 = vlSelfRef.FeedForwardMatMul__DOT__result_11_14;
    vlSelfRef.out_191 = vlSelfRef.FeedForwardMatMul__DOT__result_11_15;
    vlSelfRef.out_192 = vlSelfRef.FeedForwardMatMul__DOT__result_12_0;
    vlSelfRef.out_193 = vlSelfRef.FeedForwardMatMul__DOT__result_12_1;
    vlSelfRef.out_194 = vlSelfRef.FeedForwardMatMul__DOT__result_12_2;
    vlSelfRef.out_195 = vlSelfRef.FeedForwardMatMul__DOT__result_12_3;
    vlSelfRef.out_196 = vlSelfRef.FeedForwardMatMul__DOT__result_12_4;
    vlSelfRef.out_197 = vlSelfRef.FeedForwardMatMul__DOT__result_12_5;
    vlSelfRef.out_198 = vlSelfRef.FeedForwardMatMul__DOT__result_12_6;
    vlSelfRef.out_199 = vlSelfRef.FeedForwardMatMul__DOT__result_12_7;
    vlSelfRef.out_200 = vlSelfRef.FeedForwardMatMul__DOT__result_12_8;
    vlSelfRef.out_201 = vlSelfRef.FeedForwardMatMul__DOT__result_12_9;
    vlSelfRef.out_202 = vlSelfRef.FeedForwardMatMul__DOT__result_12_10;
    vlSelfRef.out_203 = vlSelfRef.FeedForwardMatMul__DOT__result_12_11;
    vlSelfRef.out_204 = vlSelfRef.FeedForwardMatMul__DOT__result_12_12;
    vlSelfRef.out_205 = vlSelfRef.FeedForwardMatMul__DOT__result_12_13;
    vlSelfRef.out_206 = vlSelfRef.FeedForwardMatMul__DOT__result_12_14;
    vlSelfRef.out_207 = vlSelfRef.FeedForwardMatMul__DOT__result_12_15;
    vlSelfRef.out_208 = vlSelfRef.FeedForwardMatMul__DOT__result_13_0;
    vlSelfRef.out_209 = vlSelfRef.FeedForwardMatMul__DOT__result_13_1;
    vlSelfRef.out_210 = vlSelfRef.FeedForwardMatMul__DOT__result_13_2;
    vlSelfRef.out_211 = vlSelfRef.FeedForwardMatMul__DOT__result_13_3;
    vlSelfRef.out_212 = vlSelfRef.FeedForwardMatMul__DOT__result_13_4;
    vlSelfRef.out_213 = vlSelfRef.FeedForwardMatMul__DOT__result_13_5;
    vlSelfRef.out_214 = vlSelfRef.FeedForwardMatMul__DOT__result_13_6;
    vlSelfRef.out_215 = vlSelfRef.FeedForwardMatMul__DOT__result_13_7;
    vlSelfRef.out_216 = vlSelfRef.FeedForwardMatMul__DOT__result_13_8;
    vlSelfRef.out_217 = vlSelfRef.FeedForwardMatMul__DOT__result_13_9;
    vlSelfRef.out_218 = vlSelfRef.FeedForwardMatMul__DOT__result_13_10;
    vlSelfRef.out_219 = vlSelfRef.FeedForwardMatMul__DOT__result_13_11;
    vlSelfRef.out_220 = vlSelfRef.FeedForwardMatMul__DOT__result_13_12;
    vlSelfRef.out_221 = vlSelfRef.FeedForwardMatMul__DOT__result_13_13;
    vlSelfRef.out_222 = vlSelfRef.FeedForwardMatMul__DOT__result_13_14;
    vlSelfRef.out_223 = vlSelfRef.FeedForwardMatMul__DOT__result_13_15;
    vlSelfRef.out_224 = vlSelfRef.FeedForwardMatMul__DOT__result_14_0;
    vlSelfRef.out_225 = vlSelfRef.FeedForwardMatMul__DOT__result_14_1;
    vlSelfRef.out_226 = vlSelfRef.FeedForwardMatMul__DOT__result_14_2;
    vlSelfRef.out_227 = vlSelfRef.FeedForwardMatMul__DOT__result_14_3;
    vlSelfRef.out_228 = vlSelfRef.FeedForwardMatMul__DOT__result_14_4;
    vlSelfRef.out_229 = vlSelfRef.FeedForwardMatMul__DOT__result_14_5;
    vlSelfRef.out_230 = vlSelfRef.FeedForwardMatMul__DOT__result_14_6;
    vlSelfRef.out_231 = vlSelfRef.FeedForwardMatMul__DOT__result_14_7;
    vlSelfRef.out_232 = vlSelfRef.FeedForwardMatMul__DOT__result_14_8;
    vlSelfRef.out_233 = vlSelfRef.FeedForwardMatMul__DOT__result_14_9;
    vlSelfRef.out_234 = vlSelfRef.FeedForwardMatMul__DOT__result_14_10;
    vlSelfRef.out_235 = vlSelfRef.FeedForwardMatMul__DOT__result_14_11;
    vlSelfRef.out_236 = vlSelfRef.FeedForwardMatMul__DOT__result_14_12;
    vlSelfRef.out_237 = vlSelfRef.FeedForwardMatMul__DOT__result_14_13;
    vlSelfRef.out_238 = vlSelfRef.FeedForwardMatMul__DOT__result_14_14;
    vlSelfRef.out_239 = vlSelfRef.FeedForwardMatMul__DOT__result_14_15;
    vlSelfRef.out_240 = vlSelfRef.FeedForwardMatMul__DOT__result_15_0;
    vlSelfRef.out_241 = vlSelfRef.FeedForwardMatMul__DOT__result_15_1;
    vlSelfRef.out_242 = vlSelfRef.FeedForwardMatMul__DOT__result_15_2;
    vlSelfRef.out_243 = vlSelfRef.FeedForwardMatMul__DOT__result_15_3;
    vlSelfRef.out_244 = vlSelfRef.FeedForwardMatMul__DOT__result_15_4;
    vlSelfRef.out_245 = vlSelfRef.FeedForwardMatMul__DOT__result_15_5;
    vlSelfRef.out_246 = vlSelfRef.FeedForwardMatMul__DOT__result_15_6;
    vlSelfRef.out_247 = vlSelfRef.FeedForwardMatMul__DOT__result_15_7;
    vlSelfRef.out_248 = vlSelfRef.FeedForwardMatMul__DOT__result_15_8;
    vlSelfRef.out_249 = vlSelfRef.FeedForwardMatMul__DOT__result_15_9;
    vlSelfRef.out_250 = vlSelfRef.FeedForwardMatMul__DOT__result_15_10;
    vlSelfRef.out_251 = vlSelfRef.FeedForwardMatMul__DOT__result_15_11;
    vlSelfRef.out_252 = vlSelfRef.FeedForwardMatMul__DOT__result_15_12;
    vlSelfRef.out_253 = vlSelfRef.FeedForwardMatMul__DOT__result_15_13;
    vlSelfRef.out_254 = vlSelfRef.FeedForwardMatMul__DOT__result_15_14;
    vlSelfRef.out_255 = vlSelfRef.FeedForwardMatMul__DOT__result_15_15;
}

void VFeedForwardMatMul___024root___eval_triggers__act(VFeedForwardMatMul___024root* vlSelf);

bool VFeedForwardMatMul___024root___eval_phase__act(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_phase__act\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VFeedForwardMatMul___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VFeedForwardMatMul___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VFeedForwardMatMul___024root___eval_phase__nba(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_phase__nba\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VFeedForwardMatMul___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__ico(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__nba(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__act(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG

void VFeedForwardMatMul___024root___eval(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VFeedForwardMatMul___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/matmul/verilog/FeedForwardMatMul.v", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VFeedForwardMatMul___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VFeedForwardMatMul___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/matmul/verilog/FeedForwardMatMul.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VFeedForwardMatMul___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/matmul/verilog/FeedForwardMatMul.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VFeedForwardMatMul___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VFeedForwardMatMul___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VFeedForwardMatMul___024root___eval_debug_assertions(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_debug_assertions\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
