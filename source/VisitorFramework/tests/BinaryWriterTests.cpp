#include <doctest.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <array>

#include "BinaryWriter.h"


TEST_SUITE("BinaryWriterTests")
{
    TEST_CASE("Default state")
    {
        BinaryWriter w;
        CHECK(w.Empty());
        CHECK_EQ(w.Size(), 0u);
        CHECK_EQ(w.Position(), 0u);
        CHECK(w.Buffer().empty());
        CHECK(w.Data() == w.Buffer().data());
    }

    TEST_CASE("WriteBytes writes primitive value")
    {
        BinaryWriter w;
        uint32_t val = 0x11223344u;
        w.WriteBytes(&val, sizeof(val));

        CHECK_EQ(w.Size(), sizeof(val));

        uint32_t read = 0;
        std::memcpy(&read, w.Data(), sizeof(read));
        CHECK_EQ(read, val);
    }

    TEST_CASE("Write<T> writes a value")
    {
        BinaryWriter w;
        int16_t v = -12345;
        w.Write<int16_t>(v);
        CHECK_EQ(w.Size(), sizeof(v));

        int16_t out = 0;
        std::memcpy(&out, w.Data(), sizeof(out));
        CHECK_EQ(out, v);
    }

    TEST_CASE("WriteArray (pointer) writes multiple elements")
    {
        BinaryWriter w;
        uint16_t arr[] = { 0x1111, 0x2222, 0x3333 };
        w.WriteArray<uint16_t>(arr, std::size(arr));

        CHECK_EQ(w.Size(), sizeof(arr));
        const uint16_t* data = reinterpret_cast<const uint16_t*>(w.Data());
        CHECK_EQ(data[0], arr[0]);
        CHECK_EQ(data[1], arr[1]);
        CHECK_EQ(data[2], arr[2]);
    }

    TEST_CASE("WriteArray (fixed-size) overload")
    {
        BinaryWriter w;
        uint8_t arr[4] = { 1,2,3,4 };
        w.WriteArray(arr);
        CHECK_EQ(w.Size(), 4u);
        CHECK_EQ(w.Buffer()[0], std::byte{1});
        CHECK_EQ(w.Buffer()[3], std::byte{4});
    }

    TEST_CASE("WriteString writes length prefix and data")
    {
        BinaryWriter w;
        const std::string s = "Hello";
        w.WriteString(s);

        CHECK_EQ(w.Size(), sizeof(uint32_t) + s.size());

        uint32_t len = 0;
        std::memcpy(&len, w.Data(), sizeof(len));
        CHECK_EQ(len, static_cast<uint32_t>(s.size()));

        const char* pdata = reinterpret_cast<const char*>(w.Data() + sizeof(len));
        CHECK(std::memcmp(pdata, s.data(), s.size()) == 0);
    }

    TEST_CASE("WriteString with empty string")
    {
        BinaryWriter w;
        w.WriteString(std::string_view{});
        CHECK_EQ(w.Size(), sizeof(uint32_t));
        uint32_t len = 0;
        std::memcpy(&len, w.Data(), sizeof(len));
        CHECK_EQ(len, 0u);
    }

    TEST_CASE("WriteBytes array and Pad")
    {
        BinaryWriter w;
        std::array<std::byte, 3> arr{{ std::byte{1}, std::byte{2}, std::byte{3} }};
        w.WriteBytes(arr.data(), arr.size());

        CHECK_EQ(w.Size(), arr.size());
        CHECK_EQ(w.Buffer()[0], std::byte{1});
        CHECK_EQ(w.Buffer()[1], std::byte{2});
        CHECK_EQ(w.Buffer()[2], std::byte{3});

        w.Pad(2, std::byte{0xFF});
        CHECK_EQ(w.Size(), arr.size() + 2);
        CHECK_EQ(w.Buffer()[3], std::byte{0xFF});
        CHECK_EQ(w.Buffer()[4], std::byte{0xFF});
    }

    TEST_CASE("Pad default value is zero")
    {
        BinaryWriter w;
        w.Pad(3);
        CHECK_EQ(w.Size(), 3u);
        CHECK_EQ(w.Buffer()[0], std::byte{0});
        CHECK_EQ(w.Buffer()[1], std::byte{0});
        CHECK_EQ(w.Buffer()[2], std::byte{0});
    }

    TEST_CASE("Patch in-range updates value")
    {
        BinaryWriter w;
        uint32_t a = 1, b = 2, c = 3;
        w.WriteArray<uint32_t>(std::array<uint32_t,3>{a,b,c}.data(), 3);
        // patch middle element
        uint32_t patched = 0xDEADBEEFu;
        size_t offset = sizeof(uint32_t) * 1;
        w.Patch<uint32_t>(offset, patched);

        const uint32_t* data = reinterpret_cast<const uint32_t*>(w.Data());
        CHECK_EQ(data[1], patched);
    }

    TEST_CASE("Patch out-of-range throws")
    {
        BinaryWriter w;
        uint16_t v = 0x1234;
        w.Write<uint16_t>(v);
        // attempt to patch beyond buffer
        CHECK_THROWS_AS(w.Patch<uint32_t>(1, 0u), std::out_of_range);
    }

    TEST_CASE("Clear and Reserve")
    {
        BinaryWriter w(10);
        const char sample[3] = { 0, 1, 2 };
        w.WriteBytes(sample, 3);

        CHECK_EQ(w.Size(), 3u);
        w.Clear();
        CHECK_EQ(w.Size(), 0u);
        CHECK(w.Empty());

        w.Reserve(50);
        CHECK(w.Buffer().capacity() >= 50);
    }

    TEST_CASE("Multiple writes maintain order")
    {
        BinaryWriter w;
        uint8_t a = 0xAA;
        uint16_t b = 0xBBBB;
        uint32_t c = 0xCCCCCCCC;
        w.Write<uint8_t>(a);
        w.Write<uint16_t>(b);
        w.Write<uint32_t>(c);

        const uint8_t* p = reinterpret_cast<const uint8_t*>(w.Data());
        CHECK_EQ(p[0], a);
        // check b (little-endian assumed on test machine)
        uint16_t b_read = 0;
        std::memcpy(&b_read, p + 1, sizeof(b_read));
        CHECK_EQ(b_read, b);
        uint32_t c_read = 0;
        std::memcpy(&c_read, p + 1 + sizeof(b_read), sizeof(c_read));
        CHECK_EQ(c_read, c);
    }
}
