#ifndef __OPERATOR__H__
#define __OPERATOR__H__
template <typename T, typename V = T> class IneqComparableTV {
  private:
	constexpr T const &Underlying() const { return static_cast<const T &>(*this); }
	IneqComparableTV() = default;
	~IneqComparableTV() = default;
	IneqComparableTV(const IneqComparableTV &other) = default;
	IneqComparableTV(IneqComparableTV &&other) = default;
	IneqComparableTV &operator=(const IneqComparableTV &other) = default;
	IneqComparableTV &operator=(IneqComparableTV &&other) = default;
	friend T;

  public:
	[[nodiscard]] constexpr bool operator==(const V &other) const
	{
		return !(Underlying() < other) && !(other < Underlying());
	}
	[[nodiscard]] constexpr bool operator!=(const V &other) const
	{
		return (Underlying() < other) || (other < Underlying());
	}
	[[nodiscard]] constexpr bool operator>(const V &other) const
	{
		return other < Underlying();
	}
	[[nodiscard]] constexpr bool operator>=(const V &other) const
	{
		return !(Underlying() < other);
	}
	[[nodiscard]] constexpr bool operator<=(const V &other) const
	{
		return !(other < Underlying());
	}
};
#endif
