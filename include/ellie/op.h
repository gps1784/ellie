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
    const static std::string k_s_class;
    const std::string m_s_abbr;
    std::bitset<N> m_bs_mask;
    std::bitset<N> m_bs_value;
    // functions
    // TODO: are these the most appropriate access points for an Opcode?
  public:
    op(void);
    template<typename N_size> op(std::string, N_size);
    template<typename N_size> op(std::string, N_size, N_size);
    bool     operator==(const std::bitset<N>&) const;
    bool     operator!=(const std::bitset<N>&) const;
    std::string inspect(void) const;
    const size_t   size(void);

  protected:
  private:
  };

  template<size_t N>
  const std::string op<N>::k_s_class = "ellie::op";

  template<size_t N>
  op<N>::op(void) : m_s_abbr("XXX") {
    this->m_bs_mask  = std::bitset<N>();
    this->m_bs_value = std::bitset<N>();
  }

  template<size_t N>
  template<typename N_size>
  op<N>::op(std::string p_abbr, N_size p_value) : m_s_abbr(p_abbr) {
    this->m_bs_mask  = std::bitset<N>();
    this->m_bs_value = std::bitset<N>(p_value);
    this->m_bs_mask.set(); // make this all 1s to ignore mask behavior
  }

  template<size_t N>
  template<typename N_size>
  op<N>::op(std::string p_abbr, N_size p_value, N_size p_mask) : m_s_abbr(p_abbr) {
    this->m_bs_mask  = std::bitset<N>(p_mask);
    this->m_bs_value = std::bitset<N>(p_value);
  }

  template<size_t N>
  bool op<N>::operator==(const std::bitset<N>& rhs) const {
    return this->m_bs_value == (rhs & this->m_bs_mask);
  }

  template<size_t N>
  bool op<N>::operator!=(const std::bitset<N>& rhs) const {
    return this->m_bs_value != (rhs & this->m_bs_mask);
  }

  template<size_t N>
  const size_t op<N>::size(void) {
    return this->m_bs_mask.size();
  }

  template<size_t N>
  std::string op<N>::inspect(void) const {
    return std::string("<") + k_s_class +
    " " + this->m_s_abbr + " value:0b" +
    this->m_bs_value.to_string() + " mask:0b" +
    this->m_bs_mask.to_string() + " size: " +
    std::to_string(this->m_bs_mask.size()) + " bits" +
    ">";
  }

  template<size_t N>
  std::ostream& operator<<(std::ostream& p_ostream, const op<N> p_op) {
    return (p_ostream << p_op.inspect());
  }
}

#endif
