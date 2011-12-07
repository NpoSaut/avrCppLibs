/*
 * thread-safe.h
 *
 * Потоко-безопасные переменные
 * ****************************
 *
 *  ~~~ Проблема: ~~~
 *  Если переменная используются одновременно в обработчике прерывания и коде, который может быть прерван этим прерыванием, то:
 *  1. Оптимизатор, считающий что значение переменной не может измениться из другого места, генерирует неверный код
 *  2. Если размер переменной более 1 байта, то возможна следующая ситуация:
 *     когда считана часть значения, возникнет прерывание и изменяет значение переменной,
 *     далее будет считана оставшаяся часть значени, но уже нового.
 *
 *  ~~~ Задача: ~~~
 *  1. Не использовать оптимизацию при работе с этой переменной.
 *  2. Если переменная более 1 байта, то обеспечить атомарность при чтении/записи значения:
 *  	т.е. выключать прерывания на момент чтения/записи.
 *  3. Там где это возможно обеспечить возможность обычной раобты с переменной: оптимизированной и неатомарной.
 *
 *  ~~~ Решение: ~~~
 *  1. Использовать volatile
 *  2. Исользовать ATOMIC из библиотеки Чижова
 *  3. Объединить в union volatile и не-volatile переменные.
 *
 *  ~~~ Интерфейс: ~~~
 *  Для обеспечения безопасной работы с переменной типа Type,
 *  создаётся шаблонный класс Safe<Type> и переменная объявляется этого типа.
 *  При этом:
 *  - Обычные операции присвоения и взятия значения функционируют обычно (не безопасно)
 *  - Оператор <<= обеспечивает безопасную запись и извлечение значений
 *
 *  ~~~ Комментарии: ~~~
 *  1. Атомарность обеспечивается на минимально возможном интервале:
 *     при копировании из обыной переменной в безопасную:
 *     а) сначала значение обычной переменной извлекаетс в регистры,
 *     б) потом из регистров оно записывается в безопасную переменную.
 *     Прерывания запрещены только при выполнении б)
 *  2. При использовании типа uint8_t нет необходимости в атомарности, достаточно только volatile.
 *     Поэтому для этого типа использются специализации шаблона.
 *
 *  ~~~ Пример использования: ~~~
	uint16_t v;
	Safe<uint16_t> sv;

	sv <<= v;	// Безопасное присвоение
	v <<= sv;   // Безопасное извлечение

	// В обработчике прерывания нет необходимости в безопасности,
	// там используем обычные операции:
	sv = v;
	v = sv;
 *
 */

#ifndef THREAD_SAFE_H_
#define THREAD_SAFE_H_

#include <cpp/Chizhov/AVR/atomic.h>

template<typename T>
union Safe
{
public:
	// Обычные (небезопасные) операции
	Safe (const volatile T& a)
		: generic(a) {}
	Safe (const T& a = 0)
		: generic(a) { }
//	Safe (const Safe& a) ---- вызывается автоматически вместо предыдущеги и делает overhead
//		: generic(a.generic) {}
	Safe operator= (uint16_t a)
	{
		generic = a;
		return *this;
	}
	operator T () const
	{
		return  generic;
	}
	T operator ++ (int) { return generic++; }
	T& operator ++ () { return ++generic; }
	T operator -- (int) { return generic--; }
	T& operator -- () { return --generic; }




	// Безопасные операции присваивания
	Safe& operator<<= (const volatile T& a)
	{
		T volatile temp = a;
		ATOMIC volatileX =  temp;
		return *this;
	}
	Safe& operator<<= (const T& a)
	{
		T temp = a;
		ATOMIC volatileX =  temp;
		return *this;
	}
	Safe& operator<<= (const Safe& a)
	{
		ATOMIC volatileX = a.volatileX;
		return *this;
	}
	template<typename Tt> friend Tt& operator<<= (Tt& a, const Safe<Tt>& b);
	template<typename Tt> friend volatile Tt& operator<<= (volatile Tt& a, const Safe<Tt>& b);
	// Безопасные побитовые операции
	Safe& operator&= (const volatile T& a)
	{
		T volatile temp = a;
		ATOMIC volatileX &= temp;
		return *this;
	}
	Safe& operator&= (const T& a)
	{
		T temp = a;
		ATOMIC volatileX &= temp;
		return *this;
	}
	Safe& operator&= (const Safe& a)
	{
		ATOMIC volatileX &= a.volatileX;
		return *this;
	}
	Safe& operator^= (const volatile T& a)
	{
		T volatile temp = a;
		ATOMIC volatileX ^= temp;
		return *this;
	}
	Safe& operator^= (const T& a)
	{
		T temp = a;
		ATOMIC volatileX ^= temp;
		return *this;
	}
	Safe& operator^= (const Safe& a)
	{
		ATOMIC volatileX ^= a.volatileX;
		return *this;
	}
	Safe& operator|= (const volatile T& a)
	{
		T volatile temp = a;
		ATOMIC volatileX |= temp;
		return *this;
	}
	Safe& operator|= (const T& a)
	{
		T temp = a;
		ATOMIC volatileX |= temp;
		return *this;
	}
	Safe& operator|= (const Safe& a)
	{
		ATOMIC volatileX |= a.volatileX;
		return *this;
	}
	// Аналог приведения типа
	T operator +() const
	{
		T temp;
		ATOMIC temp = volatileX;
		return temp;
	}

	T generic;

private:
	volatile T volatileX;
};

template<typename T>
inline T& operator<<= (T& a, const Safe<T>& b)
{
	T temp;
	ATOMIC temp = b.volatileX;
	a = temp;
	return a;
}
template<typename T>
inline volatile T& operator<<= (volatile T& a, const Safe<T>& b)
{
	volatile T temp;
	ATOMIC temp = b.volatileX;
	a = temp;
	return a;
}


// Для uint8_t нет необходимости в атомарности
template<>
inline Safe<uint8_t>& Safe<uint8_t>::operator<<= (const volatile uint8_t& a)
{
	volatileX =  a;
	return *this;
}
template<>
inline Safe<uint8_t>& Safe<uint8_t>::operator<<= (const uint8_t& a)
{
	volatileX =  a;
	return *this;
}
template<>
inline Safe<uint8_t>& Safe<uint8_t>::operator<<= (const Safe& a)
{
	volatileX = a.volatileX;
	return *this;
}
template<>
inline uint8_t& operator<<= (uint8_t& a, const Safe<uint8_t>& b)
{
	a = b.volatileX;
	return a;
}
template<>
inline volatile uint8_t& operator<<= (volatile uint8_t& a, const Safe<uint8_t>& b)
{
	a = b.volatileX;
	return a;
}
template<>
inline uint8_t Safe<uint8_t>::operator +() const
{
	return volatileX;
}


#endif /* THREAD_SAFE_H_ */
