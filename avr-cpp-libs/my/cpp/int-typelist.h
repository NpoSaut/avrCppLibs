/*
 * int-typelist.h
 *
 * Макросы для генерации списков типов Loki::Int2Type
 * **************************************************
 *
 *  ~~~ Проблема: ~~~
 *  Часто необходимо иметь дело со следующими списками:
 *  LOKI_TYPELIST_N (
 *  			Int2Type<x>,
 *  			Int2Type<y>,
 *  			...
 *  				)
 *
 *  ~~~ Задача: ~~~
 *  Создать макрос наподобии LOKI_TYPELIST_N, который бы позволял писать так:
 *  INT_TYPELIST_N (
 *  			x,
 *  			y,
 *  			...
 *  				)
 *
 */

#ifndef INT_TYPELIST_H_
#define INT_TYPELIST_H_

#include <cpp/loki/Typelist.h>
using namespace Loki;
using namespace ::Loki::TL;

// --------------------------------------- INT_TYPELIST -------------------------------------------
// Аналог LOKI_TYPELIST,
// но создаёт список из Int2Type
// ------------------------------------------------------------------------------------------------
#define INT_TYPELIST_1(I1) LOKI_TYPELIST_1 (Int2Type<I1>)
#define INT_TYPELIST_2(I1, I2) LOKI_TYPELIST_2 (Int2Type<I1>, Int2Type<I2>)
#define INT_TYPELIST_3(I1, I2, I3) \
	LOKI_TYPELIST_3 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>)
#define INT_TYPELIST_4(I1, I2, I3, I4) \
	LOKI_TYPELIST_4 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>)
#define INT_TYPELIST_5(I1, I2, I3, I4, I5) \
	LOKI_TYPELIST_5 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>)
#define INT_TYPELIST_6(I1, I2, I3, I4, I5, I6) \
	LOKI_TYPELIST_6 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>)
#define INT_TYPELIST_7(I1, I2, I3, I4, I5, I6, I7) \
	LOKI_TYPELIST_7 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>)
#define INT_TYPELIST_8(I1, I2, I3, I4, I5, I6, I7, I8) \
	LOKI_TYPELIST_8 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>)
#define INT_TYPELIST_9(I1, I2, I3, I4, I5, I6, I7, I8, I9) \
	LOKI_TYPELIST_9 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>)
#define INT_TYPELIST_10(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10) \
	LOKI_TYPELIST_10 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>)
#define INT_TYPELIST_11(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11) \
	LOKI_TYPELIST_11 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>)
#define INT_TYPELIST_12(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12) \
	LOKI_TYPELIST_11 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>)
#define INT_TYPELIST_13(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13) \
	LOKI_TYPELIST_13 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>)
#define INT_TYPELIST_14(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14) \
	LOKI_TYPELIST_14 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>)
#define INT_TYPELIST_15(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15) \
	LOKI_TYPELIST_15 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15>)
#define INT_TYPELIST_16(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16) \
	LOKI_TYPELIST_16 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>)
#define INT_TYPELIST_17(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17) \
	LOKI_TYPELIST_17 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>)
#define INT_TYPELIST_18(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18) \
	LOKI_TYPELIST_18 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>)
#define INT_TYPELIST_19(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19) \
	LOKI_TYPELIST_19 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>)
#define INT_TYPELIST_20(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20) \
	LOKI_TYPELIST_20 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20>)
#define INT_TYPELIST_21(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20, I21) \
	LOKI_TYPELIST_21 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20) \
			Int2Type<I21>)
#define INT_TYPELIST_22(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20, I21, I22) \
	LOKI_TYPELIST_22 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20) \
			Int2Type<I21>, Int2Type<I22>)
#define INT_TYPELIST_23(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20, I21, I22, I23) \
	LOKI_TYPELIST_23 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20) \
			Int2Type<I21>, Int2Type<I22>, Int2Type<I23>)
#define INT_TYPELIST_24(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20, I21, I22, I23, I24) \
	LOKI_TYPELIST_24 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20) \
			Int2Type<I21>, Int2Type<I22>, Int2Type<I23>, Int2Type<I24>)
#define INT_TYPELIST_25(I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, \
		I16, I17, I18, I19, I20, I21, I22, I23, I24, I25) \
	LOKI_TYPELIST_25 (Int2Type<I1>, Int2Type<I2>, Int2Type<I3>, Int2Type<I4>, Int2Type<I5>, \
			Int2Type<I6>, Int2Type<I7>, Int2Type<I8>, Int2Type<I9>, Int2Type<I10>, \
			Int2Type<I11>, Int2Type<I12>, Int2Type<I13>, Int2Type<I14>, Int2Type<I15) \
			Int2Type<I16>, Int2Type<I17>, Int2Type<I18>, Int2Type<I19>, Int2Type<I20) \
			Int2Type<I21>, Int2Type<I22>, Int2Type<I23>, Int2Type<I24>, Int2Type<I25>)

#endif /* INT_TYPELIST_H_ */
