#pragma once

#include <type_traits>

/// <summary>
/// Container for allocating raw objects without invoking a constructor
/// </summary>
/// <typeparam name="T">Type of buffered object</typeparam>
/// <typeparam name="autoDestroy">
/// Automatically pass destructor calls to the buffered object.
/// If the object has not been constructed, the destructor must support zeroed objects.
/// </typeparam>
template <typename T, bool autoDestroy = true>
struct rawalloc
{
    unsigned char buffer[sizeof(T)];

    rawalloc() : buffer{} { }

    rawalloc(const T& value)
    {
        this->val() = value;
    }

    rawalloc(T&& value) noexcept
    {
        this->val() = std::move(value);
    }

    /// <summary>
    /// Passes the destruction to the buffered object if autoDestroy is true.
    /// </summary>
    ~rawalloc()
    {
        if constexpr (autoDestroy)
            this->val().~T();
    }

    _NODISCARD T* ptr() noexcept
    {
        return reinterpret_cast<T*>(buffer);
    }

    _NODISCARD const T* ptr() const noexcept
    {
        return reinterpret_cast<const T*>(buffer);
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

    _NODISCARD const T&& val() const && noexcept
    {
        return std::move(*this->ptr());
    }

    _NODISCARD T* operator->()
    {
        return this->ptr();
    }

    _NODISCARD const T* operator->() const
    {
        return this->ptr();
    }

    _NODISCARD operator T& () & noexcept
    {
        return this->val();
    }

    _NODISCARD operator const T& () const & noexcept
    {
        return this->val();
    }

    _NODISCARD operator T& () const && noexcept
    {
        // Trying to implicitly convert from an r-value leads to an unexpected behavior of being converted to const T&.
        // Trying to overload it returning T&& would lead to ambiguities between const T& and T&& in cases such as constructors and operator=.
        static_assert(false, "Cannot implicitly cast from r-value. Use val().");
    }

    _NODISCARD T* operator&() noexcept
    {
        return this->ptr();
    }

    _NODISCARD const T* operator&() const noexcept
    {
        return this->ptr();
    }

    rawalloc operator=(const T& value)
    {
        return this->val() = value;
    }

    rawalloc operator=(T&& value) noexcept
    {
        return this->val() = std::move(value);
    }
};

template <typename T, bool autoDestroy = true>
rawalloc<T, autoDestroy>& make_raw(T& value) noexcept
{
    return reinterpret_cast<rawalloc<T, autoDestroy>&>(value);
}

template <typename T, bool autoDestroy = true>
const rawalloc<T, autoDestroy>& make_raw(const T& value) noexcept
{
    return reinterpret_cast<const rawalloc<T, autoDestroy>&>(value);
}