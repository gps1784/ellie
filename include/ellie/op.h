/* ellie/op.h
 *
 */
#ifndef ELLIE_OP_H
#define ELLIE_OP_H

#include <bitset>
#include <string>
#include <iostream>

namespace ellie {
  template<size_t N>
  class op {
    // variables
  public:
  protected:
  private:
    std::bitset<N> mask;
    std::bitset<N> value;
    // functions
    // TODO: are these the most appropriate access points for an Opcode?
  public:
    op(void);
    template<typename N_size> op(N_size);
    template<typename N_size> op(N_size, N_size);
    bool     operator==(const std::bitset<N>&) const;
    bool     operator!=(const std::bitset<N>&) const;
    bool     operator[](size_t) const;
    bool           test(size_t) const;
    std::string inspect(void) const;
    const size_t   size(void);

  protected:
  private:
  };

  template<size_t N>
  op<N>::op(void) {
    this->mask  = std::bitset<N>();
    this->value = std::bitset<N>();
  }

  template<size_t N>
  template<typename N_size>
  op<N>::op(N_size i_value) {
    this->mask  = std::bitset<N>();
    this->value = std::bitset<N>(i_value);
    this->mask.set(); // make this all 1s to ignore mask behavior
  }

  template<size_t N>
  template<typename N_size>
  op<N>::op(N_size i_value, N_size i_mask) {
    this->mask  = std::bitset<N>(i_mask);
    this->value = std::bitset<N>(i_value);
  }

  template<size_t N>
  bool op<N>::operator==(const std::bitset<N>& rhs) const {
    return this->value == (rhs & this->mask);
  }

  template<size_t N>
  bool op<N>::operator!=(const std::bitset<N>& rhs) const {
    return this->value != (rhs & this->mask);
  }

  template<size_t N>
  bool op<N>::operator[](size_t pos) const {
    return this->value[pos];
  }

  template<size_t N>
  bool op<N>::test(size_t pos) const {
    return this->value.test(pos);
  }

  /* TODO: I'd really like to be able to "assign"
     this function using a function reference.
     I haven't found a clear way to compile what I want,
     but it would look something like this:

     template<size_t N> const size_t (& op<N>::size)(void) = this->bits.size();
  */
  template<size_t N>
  const size_t op<N>::size(void) {
    return this->mask.size();
  }

  template<size_t N>
  std::string op<N>::inspect(void) const {
    return std::string("<") + " value:0b" +
    this->value.to_string() + " mask:0b" +
    this->mask.to_string() + " size: " +
    std::to_string(this->mask.size()) + " bits" +
    ">";
  }

  template<size_t N>
  std::ostream& operator<<(std::ostream& p_ostream, const op<N> p_op) {
    return (p_ostream << p_op.inspect());
  }
}

#endif
