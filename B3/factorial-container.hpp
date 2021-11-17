#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>
#include <cstddef>

namespace kosnitskiy
{
  class Factorials
  {
  public:
    class Iterator;

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type;
    using const_reference = const reference;
    using pointer = value_type;
    using const_pointer = const pointer;
    using iterator = Iterator;
    using const_iterator = iterator;
    using reverse_iterator = std::reverse_iterator<const_iterator>;
    using const_reverse_iterator = reverse_iterator;

    class Iterator: public std::iterator<iterator_category, value_type, difference_type, pointer, reference>
    {
      friend class Factorials;

    public:
      Iterator();

      reference operator*() const noexcept;
      Iterator &operator++();
      Iterator operator++(int);
      Iterator &operator--();
      Iterator operator--(int);
      bool operator==(const Iterator &src) const;
      bool operator!=(const Iterator &src) const;

    private:
      kosnitskiy::Factorials::size_type currPosition_;
      kosnitskiy::Factorials::value_type result_;

      Iterator(int index, int value);

      constexpr static int getFactorial(int number) noexcept;
    };

    bool operator==(const Factorials &/*src*/) const noexcept;
    bool operator!=(const Factorials &src) const noexcept;
    bool operator<(const Factorials &/*src*/) const noexcept;
    bool operator>(const Factorials &/*src*/) const noexcept;
    bool operator<=(const Factorials &/*src*/) const noexcept;
    bool operator>=(const Factorials &/*src*/) const noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;

    void swap(Factorials &/*src*/) const noexcept;

  private:
    static constexpr size_type beginIndex = 1;
    static constexpr size_type endIndex = 11;
  };
}

#endif //B3_FACTORIAL_CONTAINER_HPP
