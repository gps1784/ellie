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
    const static std::string k_s_class;
    const        std::string m_s_abbr;
    const     std::bitset<N> m_bs_value;
    // functions
  public:
    reg();
    reg(std::string);
    template<typename N_size> reg(std::string, N_size);
    bool operator==(const std::bitset<N>&) const;
    bool operator!=(const std::bitset<N>&) const;
    bool operator[](size_t) const;
    bool       test(size_t) const;
    const size_t size(void) const;

  protected:
  private:
  };

  template<size_t N>
  const std::string reg<N>::k_s_class = "ellie::reg";

  template<size_t N>
  reg<N>::reg() :
    m_s_abbr("UNNAMED REGISTER"),
    m_bs_value(std::bitset<N>()) {}

  template<size_t N>
  reg<N>::reg(std::string p_abbr) :
    m_s_abbr(p_abbr) {}

  template<size_t N>
  template<typename N_size>
  reg<N>::reg(std::string p_abbr, N_size p_value) :
    m_s_abbr(p_abbr),
    m_bs_value(std::bitset<N>(p_value)) {}

  template<size_t N> bool reg<N>::operator==(const std::bitset<N>& rhs) const {
    return this->m_bs_value == rhs;
  }

  template<size_t N> bool reg<N>::operator!=(const std::bitset<N>& rhs) const {
    return this->m_bs_value != rhs;
  }

  template<size_t N> bool reg<N>::operator[](size_t pos) const {
    return this->m_bs_value[pos];
  }

  template<size_t N> bool reg<N>::test(size_t pos) const {
    return this->m_bs_value.test(pos);
  }

  /* TODO: I'd really like to be able to "assign"
     this function using a function reference.
     I haven't found a clear way to compile what I want,
     but it would look something like this:

     template<size_t N> const size_t (& reg<N>::size)(void) = this->m_bs_value.size();
  */
  template<size_t N> const size_t reg<N>::size(void) const {
    return this->m_bs_value.size();
  }
}

#endif
