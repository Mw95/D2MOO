#pragma once


#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>


// Minimal arbitrary precision unsigned integer, used to replace Storm's SBig functions in the tests.
// Limbs are 32 bits, least significant first, without leading zero limbs.
class BigUnsigned
{
public:
	BigUnsigned() = default;

	explicit BigUnsigned(uint32_t nValue)
	{
		if (nValue)
		{
			m_limbs.push_back(nValue);
		}
	}

	// Little-endian bytes
	static BigUnsigned from_bytes(const uint8_t* pBytes, size_t nSize)
	{
		BigUnsigned result;
		result.m_limbs.assign((nSize + 3) / 4, 0);
		for (size_t i = 0; i < nSize; ++i)
		{
			result.m_limbs[i / 4] |= (uint32_t)pBytes[i] << (8 * (i % 4));
		}
		result.trim();
		return result;
	}

	// Little-endian bytes, without the leading zero bytes
	std::vector<uint8_t> to_bytes() const
	{
		std::vector<uint8_t> bytes;
		for (const uint32_t nLimb : m_limbs)
		{
			for (int i = 0; i < 4; ++i)
			{
				bytes.push_back((uint8_t)(nLimb >> (8 * i)));
			}
		}
		while (!bytes.empty() && bytes.back() == 0)
		{
			bytes.pop_back();
		}
		return bytes;
	}

	bool is_zero() const { return m_limbs.empty(); }

	static int compare(const BigUnsigned& a, const BigUnsigned& b)
	{
		if (a.m_limbs.size() != b.m_limbs.size())
		{
			return a.m_limbs.size() < b.m_limbs.size() ? -1 : 1;
		}
		for (size_t i = a.m_limbs.size(); i-- > 0;)
		{
			if (a.m_limbs[i] != b.m_limbs[i])
			{
				return a.m_limbs[i] < b.m_limbs[i] ? -1 : 1;
			}
		}
		return 0;
	}

	static BigUnsigned add(const BigUnsigned& a, const BigUnsigned& b)
	{
		BigUnsigned result;
		const size_t nSize = std::max(a.m_limbs.size(), b.m_limbs.size());
		result.m_limbs.resize(nSize + 1);
		uint64_t nCarry = 0;
		for (size_t i = 0; i < nSize; ++i)
		{
			nCarry += (uint64_t)a.limb(i) + b.limb(i);
			result.m_limbs[i] = (uint32_t)nCarry;
			nCarry >>= 32;
		}
		result.m_limbs[nSize] = (uint32_t)nCarry;
		result.trim();
		return result;
	}

	// a - b, 0 when b > a (the tests only subtract smaller numbers)
	static BigUnsigned sub(const BigUnsigned& a, const BigUnsigned& b)
	{
		if (compare(a, b) < 0)
		{
			return BigUnsigned();
		}

		BigUnsigned result;
		result.m_limbs.resize(a.m_limbs.size());
		int64_t nBorrow = 0;
		for (size_t i = 0; i < a.m_limbs.size(); ++i)
		{
			int64_t nValue = (int64_t)a.limb(i) - b.limb(i) - nBorrow;
			nBorrow = nValue < 0 ? 1 : 0;
			if (nValue < 0)
			{
				nValue += (int64_t)1 << 32;
			}
			result.m_limbs[i] = (uint32_t)nValue;
		}
		result.trim();
		return result;
	}

	static BigUnsigned mul(const BigUnsigned& a, const BigUnsigned& b)
	{
		BigUnsigned result;
		if (a.is_zero() || b.is_zero())
		{
			return result;
		}

		result.m_limbs.assign(a.m_limbs.size() + b.m_limbs.size(), 0);
		for (size_t i = 0; i < a.m_limbs.size(); ++i)
		{
			uint64_t nCarry = 0;
			for (size_t j = 0; j < b.m_limbs.size(); ++j)
			{
				nCarry += (uint64_t)a.m_limbs[i] * b.m_limbs[j] + result.m_limbs[i + j];
				result.m_limbs[i + j] = (uint32_t)nCarry;
				nCarry >>= 32;
			}
			result.m_limbs[i + b.m_limbs.size()] = (uint32_t)nCarry;
		}
		result.trim();
		return result;
	}

	// a % m with binary long division, m must not be zero
	static BigUnsigned mod(const BigUnsigned& a, const BigUnsigned& m)
	{
		BigUnsigned remainder;
		for (size_t nBit = a.bit_count(); nBit-- > 0;)
		{
			remainder.shift_left_one();
			if (a.bit(nBit))
			{
				if (remainder.m_limbs.empty())
				{
					remainder.m_limbs.push_back(0);
				}
				remainder.m_limbs[0] |= 1;
			}
			if (compare(remainder, m) >= 0)
			{
				remainder = sub(remainder, m);
			}
		}
		return remainder;
	}

	static BigUnsigned pow_mod(const BigUnsigned& base, const BigUnsigned& exponent, const BigUnsigned& m)
	{
		BigUnsigned result(1);
		result = mod(result, m);
		BigUnsigned power = mod(base, m);
		for (size_t nBit = 0; nBit < exponent.bit_count(); ++nBit)
		{
			if (exponent.bit(nBit))
			{
				result = mod(mul(result, power), m);
			}
			power = mod(mul(power, power), m);
		}
		return result;
	}

	bool operator==(const BigUnsigned& other) const { return m_limbs == other.m_limbs; }

private:
	uint32_t limb(size_t nIndex) const { return nIndex < m_limbs.size() ? m_limbs[nIndex] : 0; }

	size_t bit_count() const
	{
		if (m_limbs.empty())
		{
			return 0;
		}
		size_t nBits = 32 * (m_limbs.size() - 1);
		for (uint32_t nTop = m_limbs.back(); nTop; nTop >>= 1)
		{
			++nBits;
		}
		return nBits;
	}

	bool bit(size_t nBit) const { return (limb(nBit / 32) >> (nBit % 32)) & 1; }

	void shift_left_one()
	{
		uint32_t nCarry = 0;
		for (uint32_t& nLimb : m_limbs)
		{
			const uint32_t nNext = nLimb >> 31;
			nLimb = (nLimb << 1) | nCarry;
			nCarry = nNext;
		}
		if (nCarry)
		{
			m_limbs.push_back(nCarry);
		}
	}

	void trim()
	{
		while (!m_limbs.empty() && m_limbs.back() == 0)
		{
			m_limbs.pop_back();
		}
	}

	std::vector<uint32_t> m_limbs;
};
