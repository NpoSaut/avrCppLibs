/*
 * map-static.h
 *
 * Статичный ассоциативный массив
 * ******************************
 *
 *  ~~~ Проблема: ~~~
 *  Реализаций ассоциативных массивов много, но нет ни одного, который бы хорошо работал в следующих условиях:
 *  1. Статичный набор ключей, известный на момент компиляции.
 *  2. Необходимость в очень быстром доступе к элементу.
 *  3. Возможность хранить постоянные данные во flash-памяти, размеры которой на 2 порядка превосходят оперативную.
 *
 *  ~~~ Задача: ~~~
 *  Разработать свой ассоциативный массив, который бы возможно не обладал бы большой общностью,
 *  но разрешал бы существующие проблемы.
 *
 *  ~~~ Решение: ~~~
 *  1. В ОЗУ выделяется память только для нужных данных.
 *     ( => при инициализации нужно указать все используемые ключи )
 *     При доступе по значению ключа находится номер элемента в массиве и предоставляется ссылка на него.
 *	2. Для перевода ключа в номер элемента используется таблица,
 *	   в которой в ячейке с номером [ключ] хранится номер элемента в массиве.
 *	2.1  Эта таблица статична, поэтому может быть помещена во flash-память,
 *	     что при её огромном размере оправдывает её использование.
 *	2.2  Максимальное значение ключа ограничено 255.
 *	3. Если пользователь запрашивает данное по ключу, который не был указан в списке при создании,
 *	   то предоставляется доступ к специальному данному, "корзине", хранящемуся в массиве под номером 0.
 *
 *	~~~ Реализация: ~~~
 *  1. Таблица размещается во flash-памяти, поэтому она должна быть инициализирована на момент компиляции.
 *  2. Для пользователя удобно указывать используемые ключи в виде списка,
 *     он не должен сразу вручную задавать эту таблицу, потому что будет вынужден нумеровать элементы в массиве.
 *  3. Из пунктов 1 и 2 следует, что преобразования из списка ключей в указанную таблицу
 *     должно производится на момент компиляции.
 *     Т.е. по сути, для данного списка мы должны сгенерировать код, инициализирующий таблицу.
 *     Это можно сделать средствами метапрограммирования в стиле библиотеки Loki Андрея Александреску.
 *  4. Список используемых ключей задаётся как список типов Loki::Int2Type.
 *  5. Из него с помощью Numbered геренируется список пронумерованных ключей.
 *  6. Функция Val имея этот список по ключу возвращает номер, если такой ключь присутсвуют в списке,
 *     или 0, если такой ключь отсутсвует.
 *  7. Создаётся таблица размером 256 элементов, каждая ячека которой инициализируется функцией Val.
 *     Таким образом производится генерирование таблицы по списку ключей.
 *  8. Далее перегужается опретор [] таким образом, чтобы сначала по таблице получить номер элемента в массиве,
 *     а потом вернуть этот элемент.
 *
 *  ~~~ Интерфейс: ~~~
 *  Шаблонный класс MapStatic<Type, KeyList> создаёт ассоциативный массив элементов типа Type,
 *  в котором все возможные ключи перечисленны в KeyList
 *  в виде типов Loki::Int2Type в списке типов Loki::TL::Typelist.
 *	Доступ к элементам по ключам осуществляет с помощью перегруженного оператора [].
 *
 *  ~~~ Комментарии: ~~~
 *  1. Хотелось бы создавать таблицу не из 256 элементов, а из N,
 *     где N - максимальный ключь в списке используемых ключей.
 *     Но, похоже, невозможно инициализировать массив разным числом элементов.
 *     Нужен другой подход типа генерирования классов с одной статической переменной.
 *     Но тут вопрос с обращением по индексу, когда индекс не известен на момент компиляции.
 *  2. Для облегчения создания списков типов используемых клченй определены макросы INT_TYPELIST_N
 *
 *  ~~~ Пример использования: ~~~
	MapStatic < uint8_t, INT_TYPELIST_4 (
					90,
					5,
					8,
					3 ) >
		a;

	a[5] = 1;
	a[8] = 2;
	a[2] = 3; // Значение 3 удёт в "корзину"
	PORTA = a[5]; // Уйдёт 1
	PORTA = a[18]; // Уйдёт содержание корзины
 *
 */

#ifndef MAP_STATIC_H_
#define MAP_STATIC_H_

#include <avr/pgmspace.h>

#include <cpp/int-typelist.h>

// ----------------------------------------- Even -------------------------------------------------
// Из списка типов TList составляет список элементов, которые в TList находились на чётных позициях
// Список TList здесь и далее имеет тип Loki::Typelist
// ------------------------------------------------------------------------------------------------
template <class TList, bool even = true> class Even;

template <class Head, class Tail>
struct Even< Typelist<Head, Tail>, true >
{
	typedef Typelist< Head,
						typename Even<Tail, false>::Result > Result;
};

template <class Head, class Tail>
struct Even< Typelist<Head, Tail>, false >
{
	typedef typename Even<Tail, true>::Result Result;
};

template <bool even>
struct Even<NullType, even >
{
	typedef NullType Result;
};


// ------------------------------------------ Val -------------------------------------------------
// TList представляет собой список пар (ключ, значение). Ключи и значения являются типами.
// Val возвращает значение ключа n
// 				если такой ключ не найден в списке, то возвращается 0
// ------------------------------------------------------------------------------------------------
template <class n, class TList>
class Val
{
private:
	typedef typename Even<TList>::Result Keys;
	enum { findNum = IndexOf< Keys, n >::value };

public:
	typedef typename TypeAtNonStrict< TList, findNum*2 + 1, Int2Type<0> >::Result Result;
};


// ----------------------------------------- ValList ----------------------------------------------
// Для всех ключей key из KeyList выполняет Val<key, TList> формируя результат в список Result
// ------------------------------------------------------------------------------------------------
template <class KeyList, class TList> struct ValList;

template <class Head, class Tail, class TList>
struct ValList< Typelist<Head, Tail>, TList >
{
	typedef Typelist< typename Val<Head, TList>::Result,
				typename ValList<Tail, TList>::Result > Result;
};

template <class TList>
struct ValList< NullType, TList >
{
	typedef NullType Result;
};


// ---------------------------------------- Numbered -----------------------------------------------
// После каждого элемента в TList добавляет его номер в виде типа Loki::Int2Type
// Нумерация начинается с последнего элемента. Ему присваивается номер startNumber.
// -------------------------------------------------------------------------------------------------
template <class TList, int startNumber = 1> class Numbered;

	template <class Head, class Tail, int startNumber>
	class Numbered< Typelist<Head, Tail>, startNumber >
	{
	private:
		typedef Numbered<Tail, startNumber> NumTail;
	public:
		enum { number = NumTail::number + 1 };
		typedef Typelist< Head,
							Typelist< Int2Type<number>, typename NumTail::Result > > Result;
	};

	template <int startNumber>
	class Numbered< NullType, startNumber >
	{
	public:
		enum {number = startNumber - 1 };
		typedef NullType Result;
	};


// -------------------------------------- NumberedSameNum ------------------------------------------
// После каждого элемента в TList добавляет его номер в виде типа Loki::Int2Type
// Каждому элементу присваивается один и тот же номер number.
// -------------------------------------------------------------------------------------------------
template <class TList, int number> struct NumberedSameNum;

	template <class Head, class Tail, int number>
	struct NumberedSameNum< Typelist<Head, Tail>, number >
	{
		typedef Typelist < Head,
						   Typelist < Int2Type<number>, typename NumberedSameNum<Tail, number>::Result > > Result;
	};

	template <int number>
	struct NumberedSameNum< NullType, number >
	{
		typedef NullType Result;
	};


// --------------------------------------- NumberedGroup -------------------------------------------
// Из списка списков TList создаёт линейный список следующим образом:
// Если элемент в TList - одиночный тип, то после него довабляется номер в виде Loki::Int2Type
// Если элемент в TList - список типов, то каждому его элементу добавляется один и тот же номер
//                        (номер группы) и этот список пристыковывается к результату
// Номера присваиваются с конца начиная с startNumber.
// -------------------------------------------------------------------------------------------------
template <class TList, int startNumber = 1> class NumberedGroup;

	template <class H, class T, class Tail, int startNumber>
	class NumberedGroup< Typelist< Typelist<H, T>, Tail>, startNumber >
	{
	private:
		typedef Numbered<Tail, startNumber> NumTail;
	public:
		enum { number = NumTail::number + 1 };
		typedef Append<
					typename NumberedSameNum< Typelist<H, T>, number >::Result,
					typename NumTail::Result
					  > Result;
	};

	template <class Head, class Tail, int startNumber>
	class NumberedGroup< Typelist<Head, Tail>, startNumber >
	{
	private:
		typedef Numbered<Tail, startNumber> NumTail;
	public:
		enum { number = NumTail::number + 1 };
		typedef Typelist <
						Head,
						Typelist< Int2Type<number>,	typename NumTail::Result >
						 > Result;
	};

	template <int startNumber>
	class NumberedGroup< NullType, startNumber >
	{
	public:
		enum { number = startNumber - 1 };
		typedef NullType Result;
	};


// ----------------------------------------- ReIndex ----------------------------------------------
// TList является списком (ключ, значение), где ключи и значения являются типами Loki::Int2Type.
// ReIndex представляет этот список в виде массива, в котором в ячейке с номером n находится:
// 				0, если в исходном списке не было записей с ключом n
//			value, если в исходном списке содержалась запись (n, value)
// Этот массив помещается во flash-памяти
// Ключи и значения являются uint8_t. Для ReIndex16 максимальный ключ 15. Для ReIndex256 -- 255.
// Соответсвенно массив занимает 16 или 256 байт.
// ------------------------------------------------------------------------------------------------
template <class TList>
class ReIndex16
{
public:
	uint8_t operator[] (const uint8_t& key) { return pgm_read_byte(&array[key]); }
private:
	static uint8_t array[16] __attribute__ ((section (".text")));
};

template <class TList>
uint8_t ReIndex16<TList>::array[16]=	{ Val< Int2Type<  0>,	TList >::Result::value,
									  Val< Int2Type<  1>,	TList >::Result::value,
									  Val< Int2Type<  2>,	TList >::Result::value,
									  Val< Int2Type<  3>,	TList >::Result::value,
									  Val< Int2Type<  4>,	TList >::Result::value,
									  Val< Int2Type<  5>,	TList >::Result::value,
									  Val< Int2Type<  6>,	TList >::Result::value,
									  Val< Int2Type<  7>,	TList >::Result::value,
									  Val< Int2Type<  8>,	TList >::Result::value,
									  Val< Int2Type<  9>,	TList >::Result::value,
									  Val< Int2Type< 10>,	TList >::Result::value,
									  Val< Int2Type< 11>,	TList >::Result::value,
									  Val< Int2Type< 12>,	TList >::Result::value,
									  Val< Int2Type< 13>,	TList >::Result::value,
									  Val< Int2Type< 14>,	TList >::Result::value,
									  Val< Int2Type< 15>,	TList >::Result::value,
									 };


template <class TList>
class ReIndex256
{
public:
	uint8_t operator[] (const uint8_t& key) { return pgm_read_byte(&array[key]); }
private:
	static uint8_t array[256] __attribute__ ((section (".text")));
};

template <class TList>
uint8_t ReIndex256<TList>::array[256]=	{ Val< Int2Type<  0>,	TList >::Result::value,
									  Val< Int2Type<  1>,	TList >::Result::value,
									  Val< Int2Type<  2>,	TList >::Result::value,
									  Val< Int2Type<  3>,	TList >::Result::value,
									  Val< Int2Type<  4>,	TList >::Result::value,
									  Val< Int2Type<  5>,	TList >::Result::value,
									  Val< Int2Type<  6>,	TList >::Result::value,
									  Val< Int2Type<  7>,	TList >::Result::value,
									  Val< Int2Type<  8>,	TList >::Result::value,
									  Val< Int2Type<  9>,	TList >::Result::value,
									  Val< Int2Type< 10>,	TList >::Result::value,
									  Val< Int2Type< 11>,	TList >::Result::value,
									  Val< Int2Type< 12>,	TList >::Result::value,
									  Val< Int2Type< 13>,	TList >::Result::value,
									  Val< Int2Type< 14>,	TList >::Result::value,
									  Val< Int2Type< 15>,	TList >::Result::value,
									  Val< Int2Type< 16>,	TList >::Result::value,
									  Val< Int2Type< 17>,	TList >::Result::value,
									  Val< Int2Type< 18>,	TList >::Result::value,
									  Val< Int2Type< 19>,	TList >::Result::value,
									  Val< Int2Type< 20>,	TList >::Result::value,
									  Val< Int2Type< 21>,	TList >::Result::value,
									  Val< Int2Type< 22>,	TList >::Result::value,
									  Val< Int2Type< 23>,	TList >::Result::value,
									  Val< Int2Type< 24>,	TList >::Result::value,
									  Val< Int2Type< 25>,	TList >::Result::value,
									  Val< Int2Type< 26>,	TList >::Result::value,
									  Val< Int2Type< 27>,	TList >::Result::value,
									  Val< Int2Type< 28>,	TList >::Result::value,
									  Val< Int2Type< 29>,	TList >::Result::value,
									  Val< Int2Type< 30>,	TList >::Result::value,
									  Val< Int2Type< 31>,	TList >::Result::value,
									  Val< Int2Type< 32>,	TList >::Result::value,
									  Val< Int2Type< 33>,	TList >::Result::value,
									  Val< Int2Type< 34>,	TList >::Result::value,
									  Val< Int2Type< 35>,	TList >::Result::value,
									  Val< Int2Type< 36>,	TList >::Result::value,
									  Val< Int2Type< 37>,	TList >::Result::value,
									  Val< Int2Type< 38>,	TList >::Result::value,
									  Val< Int2Type< 39>,	TList >::Result::value,
									  Val< Int2Type< 40>,	TList >::Result::value,
									  Val< Int2Type< 41>,	TList >::Result::value,
									  Val< Int2Type< 42>,	TList >::Result::value,
									  Val< Int2Type< 43>,	TList >::Result::value,
									  Val< Int2Type< 44>,	TList >::Result::value,
									  Val< Int2Type< 45>,	TList >::Result::value,
									  Val< Int2Type< 46>,	TList >::Result::value,
									  Val< Int2Type< 47>,	TList >::Result::value,
									  Val< Int2Type< 48>,	TList >::Result::value,
									  Val< Int2Type< 49>,	TList >::Result::value,
									  Val< Int2Type< 50>,	TList >::Result::value,
									  Val< Int2Type< 51>,	TList >::Result::value,
									  Val< Int2Type< 52>,	TList >::Result::value,
									  Val< Int2Type< 53>,	TList >::Result::value,
									  Val< Int2Type< 54>,	TList >::Result::value,
									  Val< Int2Type< 55>,	TList >::Result::value,
									  Val< Int2Type< 56>,	TList >::Result::value,
									  Val< Int2Type< 57>,	TList >::Result::value,
									  Val< Int2Type< 58>,	TList >::Result::value,
									  Val< Int2Type< 59>,	TList >::Result::value,
									  Val< Int2Type< 60>,	TList >::Result::value,
									  Val< Int2Type< 61>,	TList >::Result::value,
									  Val< Int2Type< 62>,	TList >::Result::value,
									  Val< Int2Type< 63>,	TList >::Result::value,
									  Val< Int2Type< 64>,	TList >::Result::value,
									  Val< Int2Type< 65>,	TList >::Result::value,
									  Val< Int2Type< 66>,	TList >::Result::value,
									  Val< Int2Type< 67>,	TList >::Result::value,
									  Val< Int2Type< 68>,	TList >::Result::value,
									  Val< Int2Type< 69>,	TList >::Result::value,
									  Val< Int2Type< 70>,	TList >::Result::value,
									  Val< Int2Type< 71>,	TList >::Result::value,
									  Val< Int2Type< 72>,	TList >::Result::value,
									  Val< Int2Type< 73>,	TList >::Result::value,
									  Val< Int2Type< 74>,	TList >::Result::value,
									  Val< Int2Type< 75>,	TList >::Result::value,
									  Val< Int2Type< 76>,	TList >::Result::value,
									  Val< Int2Type< 77>,	TList >::Result::value,
									  Val< Int2Type< 78>,	TList >::Result::value,
									  Val< Int2Type< 79>,	TList >::Result::value,
									  Val< Int2Type< 80>,	TList >::Result::value,
									  Val< Int2Type< 81>,	TList >::Result::value,
									  Val< Int2Type< 82>,	TList >::Result::value,
									  Val< Int2Type< 83>,	TList >::Result::value,
									  Val< Int2Type< 84>,	TList >::Result::value,
									  Val< Int2Type< 85>,	TList >::Result::value,
									  Val< Int2Type< 86>,	TList >::Result::value,
									  Val< Int2Type< 87>,	TList >::Result::value,
									  Val< Int2Type< 88>,	TList >::Result::value,
									  Val< Int2Type< 89>,	TList >::Result::value,
									  Val< Int2Type< 90>,	TList >::Result::value,
									  Val< Int2Type< 91>,	TList >::Result::value,
									  Val< Int2Type< 92>,	TList >::Result::value,
									  Val< Int2Type< 93>,	TList >::Result::value,
									  Val< Int2Type< 94>,	TList >::Result::value,
									  Val< Int2Type< 95>,	TList >::Result::value,
									  Val< Int2Type< 96>,	TList >::Result::value,
									  Val< Int2Type< 97>,	TList >::Result::value,
									  Val< Int2Type< 98>,	TList >::Result::value,
									  Val< Int2Type< 99>,	TList >::Result::value,
									  Val< Int2Type<100>,	TList >::Result::value,
									  Val< Int2Type<101>,	TList >::Result::value,
									  Val< Int2Type<102>,	TList >::Result::value,
									  Val< Int2Type<103>,	TList >::Result::value,
									  Val< Int2Type<104>,	TList >::Result::value,
									  Val< Int2Type<105>,	TList >::Result::value,
									  Val< Int2Type<106>,	TList >::Result::value,
									  Val< Int2Type<107>,	TList >::Result::value,
									  Val< Int2Type<108>,	TList >::Result::value,
									  Val< Int2Type<109>,	TList >::Result::value,
									  Val< Int2Type<110>,	TList >::Result::value,
									  Val< Int2Type<111>,	TList >::Result::value,
									  Val< Int2Type<112>,	TList >::Result::value,
									  Val< Int2Type<113>,	TList >::Result::value,
									  Val< Int2Type<114>,	TList >::Result::value,
									  Val< Int2Type<115>,	TList >::Result::value,
									  Val< Int2Type<116>,	TList >::Result::value,
									  Val< Int2Type<117>,	TList >::Result::value,
									  Val< Int2Type<118>,	TList >::Result::value,
									  Val< Int2Type<119>,	TList >::Result::value,
									  Val< Int2Type<120>,	TList >::Result::value,
									  Val< Int2Type<121>,	TList >::Result::value,
									  Val< Int2Type<122>,	TList >::Result::value,
									  Val< Int2Type<123>,	TList >::Result::value,
									  Val< Int2Type<124>,	TList >::Result::value,
									  Val< Int2Type<125>,	TList >::Result::value,
									  Val< Int2Type<126>,	TList >::Result::value,
									  Val< Int2Type<127>,	TList >::Result::value,
									  Val< Int2Type<128>,	TList >::Result::value,
									  Val< Int2Type<129>,	TList >::Result::value,
									  Val< Int2Type<130>,	TList >::Result::value,
									  Val< Int2Type<131>,	TList >::Result::value,
									  Val< Int2Type<132>,	TList >::Result::value,
									  Val< Int2Type<133>,	TList >::Result::value,
									  Val< Int2Type<134>,	TList >::Result::value,
									  Val< Int2Type<135>,	TList >::Result::value,
									  Val< Int2Type<136>,	TList >::Result::value,
									  Val< Int2Type<137>,	TList >::Result::value,
									  Val< Int2Type<138>,	TList >::Result::value,
									  Val< Int2Type<139>,	TList >::Result::value,
									  Val< Int2Type<140>,	TList >::Result::value,
									  Val< Int2Type<141>,	TList >::Result::value,
									  Val< Int2Type<142>,	TList >::Result::value,
									  Val< Int2Type<143>,	TList >::Result::value,
									  Val< Int2Type<144>,	TList >::Result::value,
									  Val< Int2Type<145>,	TList >::Result::value,
									  Val< Int2Type<146>,	TList >::Result::value,
									  Val< Int2Type<147>,	TList >::Result::value,
									  Val< Int2Type<148>,	TList >::Result::value,
									  Val< Int2Type<149>,	TList >::Result::value,
									  Val< Int2Type<150>,	TList >::Result::value,
									  Val< Int2Type<151>,	TList >::Result::value,
									  Val< Int2Type<152>,	TList >::Result::value,
									  Val< Int2Type<153>,	TList >::Result::value,
									  Val< Int2Type<154>,	TList >::Result::value,
									  Val< Int2Type<155>,	TList >::Result::value,
									  Val< Int2Type<156>,	TList >::Result::value,
									  Val< Int2Type<157>,	TList >::Result::value,
									  Val< Int2Type<158>,	TList >::Result::value,
									  Val< Int2Type<159>,	TList >::Result::value,
									  Val< Int2Type<160>,	TList >::Result::value,
									  Val< Int2Type<161>,	TList >::Result::value,
									  Val< Int2Type<162>,	TList >::Result::value,
									  Val< Int2Type<163>,	TList >::Result::value,
									  Val< Int2Type<164>,	TList >::Result::value,
									  Val< Int2Type<165>,	TList >::Result::value,
									  Val< Int2Type<166>,	TList >::Result::value,
									  Val< Int2Type<167>,	TList >::Result::value,
									  Val< Int2Type<168>,	TList >::Result::value,
									  Val< Int2Type<169>,	TList >::Result::value,
									  Val< Int2Type<170>,	TList >::Result::value,
									  Val< Int2Type<171>,	TList >::Result::value,
									  Val< Int2Type<172>,	TList >::Result::value,
									  Val< Int2Type<173>,	TList >::Result::value,
									  Val< Int2Type<174>,	TList >::Result::value,
									  Val< Int2Type<175>,	TList >::Result::value,
									  Val< Int2Type<176>,	TList >::Result::value,
									  Val< Int2Type<177>,	TList >::Result::value,
									  Val< Int2Type<178>,	TList >::Result::value,
									  Val< Int2Type<179>,	TList >::Result::value,
									  Val< Int2Type<180>,	TList >::Result::value,
									  Val< Int2Type<181>,	TList >::Result::value,
									  Val< Int2Type<182>,	TList >::Result::value,
									  Val< Int2Type<183>,	TList >::Result::value,
									  Val< Int2Type<184>,	TList >::Result::value,
									  Val< Int2Type<185>,	TList >::Result::value,
									  Val< Int2Type<186>,	TList >::Result::value,
									  Val< Int2Type<187>,	TList >::Result::value,
									  Val< Int2Type<188>,	TList >::Result::value,
									  Val< Int2Type<189>,	TList >::Result::value,
									  Val< Int2Type<190>,	TList >::Result::value,
									  Val< Int2Type<191>,	TList >::Result::value,
									  Val< Int2Type<192>,	TList >::Result::value,
									  Val< Int2Type<193>,	TList >::Result::value,
									  Val< Int2Type<194>,	TList >::Result::value,
									  Val< Int2Type<195>,	TList >::Result::value,
									  Val< Int2Type<196>,	TList >::Result::value,
									  Val< Int2Type<197>,	TList >::Result::value,
									  Val< Int2Type<198>,	TList >::Result::value,
									  Val< Int2Type<199>,	TList >::Result::value,
									  Val< Int2Type<200>,	TList >::Result::value,
									  Val< Int2Type<201>,	TList >::Result::value,
									  Val< Int2Type<202>,	TList >::Result::value,
									  Val< Int2Type<203>,	TList >::Result::value,
									  Val< Int2Type<204>,	TList >::Result::value,
									  Val< Int2Type<205>,	TList >::Result::value,
									  Val< Int2Type<206>,	TList >::Result::value,
									  Val< Int2Type<207>,	TList >::Result::value,
									  Val< Int2Type<208>,	TList >::Result::value,
									  Val< Int2Type<209>,	TList >::Result::value,
									  Val< Int2Type<210>,	TList >::Result::value,
									  Val< Int2Type<211>,	TList >::Result::value,
									  Val< Int2Type<212>,	TList >::Result::value,
									  Val< Int2Type<213>,	TList >::Result::value,
									  Val< Int2Type<214>,	TList >::Result::value,
									  Val< Int2Type<215>,	TList >::Result::value,
									  Val< Int2Type<216>,	TList >::Result::value,
									  Val< Int2Type<217>,	TList >::Result::value,
									  Val< Int2Type<218>,	TList >::Result::value,
									  Val< Int2Type<219>,	TList >::Result::value,
									  Val< Int2Type<220>,	TList >::Result::value,
									  Val< Int2Type<221>,	TList >::Result::value,
									  Val< Int2Type<222>,	TList >::Result::value,
									  Val< Int2Type<223>,	TList >::Result::value,
									  Val< Int2Type<224>,	TList >::Result::value,
									  Val< Int2Type<225>,	TList >::Result::value,
									  Val< Int2Type<226>,	TList >::Result::value,
									  Val< Int2Type<227>,	TList >::Result::value,
									  Val< Int2Type<228>,	TList >::Result::value,
									  Val< Int2Type<229>,	TList >::Result::value,
									  Val< Int2Type<230>,	TList >::Result::value,
									  Val< Int2Type<231>,	TList >::Result::value,
									  Val< Int2Type<232>,	TList >::Result::value,
									  Val< Int2Type<233>,	TList >::Result::value,
									  Val< Int2Type<234>,	TList >::Result::value,
									  Val< Int2Type<235>,	TList >::Result::value,
									  Val< Int2Type<236>,	TList >::Result::value,
									  Val< Int2Type<237>,	TList >::Result::value,
									  Val< Int2Type<238>,	TList >::Result::value,
									  Val< Int2Type<239>,	TList >::Result::value,
									  Val< Int2Type<240>,	TList >::Result::value,
									  Val< Int2Type<241>,	TList >::Result::value,
									  Val< Int2Type<242>,	TList >::Result::value,
									  Val< Int2Type<243>,	TList >::Result::value,
									  Val< Int2Type<244>,	TList >::Result::value,
									  Val< Int2Type<245>,	TList >::Result::value,
									  Val< Int2Type<246>,	TList >::Result::value,
									  Val< Int2Type<247>,	TList >::Result::value,
									  Val< Int2Type<248>,	TList >::Result::value,
									  Val< Int2Type<249>,	TList >::Result::value,
									  Val< Int2Type<250>,	TList >::Result::value,
									  Val< Int2Type<251>,	TList >::Result::value,
									  Val< Int2Type<252>,	TList >::Result::value,
									  Val< Int2Type<253>,	TList >::Result::value,
									  Val< Int2Type<254>,	TList >::Result::value,
									  Val< Int2Type<255>,	TList >::Result::value
									 };


// ----------------------------------------- MapStatic --------------------------------------------
// Представляет собой ассоциативный массив,
//	в котором все возможные ключи заданы на момент компиляции списком KeyList. (элементы Int2Type)
// Type - тип хранимых значений
// Реализуется хеш-функцией, которая представляет собой таблицу во flash-памяти.
//	В зависимости от максимального значения ключа выбирается версия 16 или 256.
//	Соответсвенно в flash-памяти они будут занимать 16 или 256 байт.
// ------------------------------------------------------------------------------------------------
template <class Type, class KeyList>
class MapStatic16
{
public:
	Type& operator[] (uint8_t key) { return data[ hash[key] ]; }

private:
	ReIndex16< typename Numbered<KeyList>::Result > hash;
	Type data[ Length<KeyList>::value + 1 ];
};

template <class Type, class KeyList>
class MapStatic256
{
public:
	Type& operator[] (uint8_t key) { return data[ hash[key] ]; }

private:
	ReIndex256< typename Numbered<KeyList>::Result > hash;
	Type data[ Length<KeyList>::value + 1 ];
};

#endif /* MAP_STATIC_H_ */
