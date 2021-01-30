/* ellie/reg.h
 *
 */
#ifndef ELLIE_REG_H
#define ELLIE_REG_H

#include <bitset>

namespace ellie {
  template<size_t N>
  class reg {
    // variables
  public:
  protected:
  private:
    std::bitset<N> bits;
    // functions
  public:
    reg(void);
    bool operator==(const std::bitset<N>&) const;
    bool operator!=(const std::bitset<N>&) const;
    bool operator[](size_t) const;
    bool       test(size_t) const;
    const size_t size(void);

  protected:
  private:
  };

  template<size_t N>
  reg<N>::reg(void) {
    this->bits = std::bitset<N>();
  }

  template<size_t N> bool reg<N>::operator==(const std::bitset<N>& rhs) const {
    return this->bits == rhs;
  }

  template<size_t N> bool reg<N>::operator!=(const std::bitset<N>& rhs) const {
    return this->bits != rhs;
  }

  template<size_t N> bool reg<N>::operator[](size_t pos) const {
    return this->bits[pos];
  }

  template<size_t N> bool reg<N>::test(size_t pos) const {
    return this->bits.test(pos);
  }

  /* TODO: I'd really like to be able to "assign"
     this function using a function reference.
     I haven't found a clear way to compile what I want,
     but it would look something like this:

     template<size_t N> const size_t (& reg<N>::size)(void) = this->bits.size();
  */
  template<size_t N> const size_t reg<N>::size(void) {
    return this->bits.size();
  }
}

#endif
