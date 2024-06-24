#ifndef BITSET_BITSET_HPP
#define BITSET_BITSET_HPP

#include <vector>

class BitSet {
public:
  class BiA {
  public:
    BiA() = delete;
    BiA(BitSet& bs, const int32_t idx)
      : bs_(bs), idx_(idx)
    {
    };
    ~BiA() = default;

    BiA(const BiA&) = delete;

    BiA(BiA&&) noexcept = default;

    BiA& operator=(const bool rhs) noexcept {
      bs_.Set(idx_, rhs);
      return *this;
    };

    BiA& operator=(const BiA& rhs) {
      bs_.Set(idx_, rhs.bs_.Get(rhs.idx_));
      return *this;
    };
    
    BiA& operator=(BiA&& rhs) noexcept {
      bs_.Set(idx_, rhs.bs_.Get(rhs.idx_));
      return *this;
    };

    bool operator==(const bool rhs) noexcept {
      return (bs_.Get(idx_) == rhs);
    };

    bool operator!=(const bool rhs) noexcept {
      return !(operator==(rhs));
    };

    [[nodiscard]] operator bool() const {
      return bs_.Get(idx_);
    }

  private:
    BitSet& bs_;
    int32_t idx_;
  };


  BitSet() = default;
  BitSet(const BitSet&);
  BitSet(const int32_t size);
  BitSet(BitSet&&) noexcept;
  ~BitSet() = default;

  BitSet& operator=(const BitSet& rhs) noexcept;
  BitSet& operator=(BitSet&& rhs) noexcept;

  int32_t Size() const noexcept { return size_; }
  void Resize(const int32_t& size);
  bool Get(const int32_t& idx) const;
  void Set(const int32_t& idx, const bool v);
  void Fill(const bool val) noexcept;

  BiA operator[](const int32_t i);

  BitSet operator~() const noexcept;

  bool operator==(const BitSet& rhs) const;
  bool operator!=(const BitSet& rhs) const { return !operator==(rhs); }

  BitSet& operator&=(const BitSet& rhs);
  
  BitSet& operator^=(const BitSet& rhs);

  BitSet& operator|=(const BitSet& rhs);

private:
  std::vector<uint32_t> data_;
  int32_t size_ = 0;
};

BitSet operator&(const BitSet& lhs, const BitSet& rhs);
BitSet operator^(const BitSet& lhs, const BitSet& rhs);
BitSet operator|(const BitSet& lhs, const BitSet& rhs);

#endif // !BITSET_BITSET_HPP
