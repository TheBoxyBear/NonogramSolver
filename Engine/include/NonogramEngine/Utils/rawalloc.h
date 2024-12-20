#pragma once

#include <xutility>

/// <summary>
/// Container for allocating raw objects without invoking a constructor or destructor
/// </summary>
/// <typeparam name="T">Type of buffered object</typeparam>
template <typename T>
struct rawalloc
{
    unsigned char buffer[sizeof(T)] {};

    rawalloc() = default;

    rawalloc(const T& value)
    {
        this->val() = value;
    }

    rawalloc(T&& value) noexcept
    {
        this->val() = std::move(value);
    }

	rawalloc(const rawalloc& other)
	{
		this->val() = other.val();
	}

	rawalloc(rawalloc&& other) noexcept
	{
		this->val() = std::move(other.val());
	}

    rawalloc& operator=(const T& value)
    {
        this->val() = value;
        return *this;
    }

    rawalloc& operator=(T&& value) noexcept
    {
        this->val() = std::move(value);
		return *this;
    }

    rawalloc& operator=(const rawalloc& other)
    {
		return *this = other.val();
    }

    rawalloc& operator=(rawalloc&& other) noexcept
    {
        return *this = std::move(other.val());
    }

    _NODISCARD T* ptr() noexcept
    {
        return reinterpret_cast<T*>(buffer);
    }

    _NODISCARD const T* ptr() const noexcept
    {
        return const_cast<rawalloc>(this)->ptr();
    }

    _NODISCARD T& val() & noexcept
    {
        return *this->ptr();
    }

    _NODISCARD const T& val() const & noexcept
    {
        return *this->ptr();
    }

    _NODISCARD T&& val() && noexcept
    {
        return std::move(*this->ptr());
    }

    _NODISCARD T* operator->() noexcept
    {
        return this->ptr();
    }

    _NODISCARD const T* operator->() const noexcept
    {
        return this->ptr();
    }

    _NODISCARD T& operator*() noexcept
    {
        return this->val();
    }

    _NODISCARD const T& operator*() const noexcept
    {
        return this->val();
    }

    _NODISCARD T* operator&() noexcept
    {
        return this->ptr();
    }

    _NODISCARD const T* operator&() const noexcept
    {
        return this->ptr();
    }
};

template <typename T>
rawalloc<T>& make_raw(T& value) noexcept
{
    return reinterpret_cast<rawalloc<T>&>(value);
}

template <typename T>
const rawalloc<T>& make_raw(const T& value) noexcept
{
	return make_raw(const_cast<T&>(value));
}
