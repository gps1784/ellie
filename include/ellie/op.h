/* ellie/op.h
 *
 * 2021-02-01 I've decided that name, value, and mask should
 *   all be constants. there's just no reason to modify these
 *   after creation and it would only expose the need for another
 *   public access point into the class to allow that.
 *   Additionally, there is no op::op(void) because you should
 *   NEVER intentionally be creating a void opcode?
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
    const        std::string m_s_abbr;
    const     std::bitset<N> m_bs_value;
    const     std::bitset<N> m_bs_mask;
    // functions
    // TODO: are these the most appropriate access points for an Opcode?
  public:
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
  template<typename N_size>
  op<N>::op(std::string p_abbr, N_size p_value) :
    m_s_abbr(p_abbr),
    m_bs_value(std::bitset<N>(p_value)),
    m_bs_mask(std::bitset<N>().set()) {} // all true to ignore masking

  template<size_t N>
  template<typename N_size>
  op<N>::op(std::string p_abbr, N_size p_value, N_size p_mask) :
    m_s_abbr(p_abbr),
    m_bs_value(std::bitset<N>(p_value)),
    m_bs_mask(std::bitset<N>(p_mask)) {}

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
    return this->m_bs_value.size();
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
