#pragma once

#include "UnsafeVboFactory.h"
#include "VboType.h"

namespace GlEngine
{
    template <VboType type, typename T>
    struct vbo_attribs;

    template <VboType type, typename T = void, typename... TArgs>
    struct compound_vbo_attribs
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = vbo_attribs<type, T>::element_count + compound_vbo_attribs<type, TArgs...>::element_count;
        inline static void push(T val, TArgs... others, std::vector<el_type> &values)
        {
            vbo_attribs<type, T>::push(val, values);
            compound_vbo_attribs<type, TArgs...>::push(others..., values);
        }

        inline static int check_whole_cache(T val, TArgs... others, std::vector<el_type> &values)
        {
            auto numElements = values.size() / element_count;
            for (size_t q = 0; q < numElements; q++)
            {
                if (check_cache(q * element_count, val, others..., values))
                    return q;
            }
            return -1;
        }
        inline static bool check_cache(unsigned offset, T val, TArgs... others, std::vector<el_type> &values)
        {
            if (!vbo_attribs<type, T>::check_cache(offset, val, values)) return false;
            return compound_vbo_attribs<type, TArgs...>::check_cache(offset + vbo_attribs<type, T>::element_count, others..., values);
        }

        static const unsigned attrib_count = 1 + compound_vbo_attribs<type, TArgs...>::attrib_count;
        template <unsigned attribCount = attrib_count, unsigned idx = 0, unsigned start = 0>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount> &factory)
        {
            static const unsigned elCount = vbo_attribs<type, T>::element_count;
            factory.AddAttrib(idx, start, elCount);
            compound_vbo_attribs<type, TArgs...>::add_attribs<attribCount, idx + 1, start + (elCount * sizeof(el_type))>(factory);
        }
    };

    template <VboType type>
    struct compound_vbo_attribs<type, void>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = 0;
        static const unsigned attrib_count = 0;
        inline static void push(std::vector<el_type>&)
        {
        }
        inline static bool check_cache(unsigned, std::vector<el_type>&)
        {
            return true;
        }
        template <unsigned attribCount = attrib_count, unsigned idx = 0, unsigned start = 0>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount>&)
        {
        }
    };

    template <VboType type>
    struct vbo_attribs<type, typename vbo_type_attribs<type>::type>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = 1;
        inline static void push(const el_type &val, std::vector<el_type> &values)
        {
            values.push_back(val);
        }
        inline static bool check_cache(unsigned offset, el_type val, std::vector<el_type> &values)
        {
            return (values[offset] == val);
        }
    };

 //   template <>
 //   struct vbo_attribs<VboType::Int, int32_t>
 //   {
 //       static const unsigned element_count = 1;
 //       inline static void push(const int32_t &val, std::vector<int32_t> &values)
 //       {
 //           values.push_back(val);
 //       }
 //       inline static bool check_cache(unsigned offset, const int32_t &val, std::vector<int32_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
 //   };
 //   template <>
 //   struct vbo_attribs<VboType::UnsignedInt, uint32_t>
 //   {
 //       static const unsigned element_count = 1;
 //       inline static void push(const uint32_t &val, std::vector<uint32_t> &values)
 //       {
 //           values.push_back(val);
 //       }
 //       inline static bool check_cache(unsigned offset, const uint32_t &val, std::vector<uint32_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
 //   };

	//template <>
	//struct vbo_attribs<VboType::Short, int16_t>
	//{
	//	static const unsigned element_count = 1;
	//	inline static void push(const int16_t &val, std::vector<int16_t> &values)
	//	{
	//		values.push_back(val);
	//	}
 //       inline static bool check_cache(unsigned offset, const int16_t &val, std::vector<int16_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
	//};
	//template <>
	//struct vbo_attribs<VboType::UnsignedShort, uint16_t>
	//{
	//	static const unsigned element_count = 1;
	//	inline static void push(const uint16_t &val, std::vector<uint16_t> &values)
	//	{
	//		values.push_back(val);
	//	}
 //       inline static bool check_cache(unsigned offset, const uint16_t &val, std::vector<uint16_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
	//};

	//template <>
	//struct vbo_attribs<VboType::Byte, int8_t>
	//{
	//	static const unsigned element_count = 1;
	//	inline static void push(const int8_t &val, std::vector<int8_t> &values)
	//	{
	//		values.push_back(val);
	//	}
 //       inline static bool check_cache(unsigned offset, const int8_t &val, std::vector<int8_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
	//};
	//template <>
	//struct vbo_attribs<VboType::UnsignedByte, uint8_t>
	//{
	//	static const unsigned element_count = 1;
	//	inline static void push(const uint8_t &val, std::vector<uint8_t> &values)
	//	{
	//		values.push_back(val);
	//	}
 //       inline static bool check_cache(unsigned offset, const uint8_t &val, std::vector<uint8_t> &values)
 //       {
 //           return (values[offset] == val);
 //       }
	//};

 //   template <>
 //   struct vbo_attribs<VboType::Float, float>
 //   {
 //       static const unsigned element_count = 1;
 //       inline static void push(const float &val, std::vector<float> &values)
 //       {
 //           values.push_back(val);
 //       }
 //       inline static bool check_cache(unsigned offset, const float &val, std::vector<float> &values)
 //       {
 //           return (values[offset] == val);
 //       }
 //   };

    template <>
    struct vbo_attribs<VboType::Double, float>
    {
        static const unsigned element_count = 1;
        inline static void push(const float &val, std::vector<double> &values)
        {
            values.push_back((double)val);
        }
        inline static bool check_cache(unsigned offset, const float &val, std::vector<double> &values)
        {
            return (values[offset] == val);
        }
    };
    //template <>
    //struct vbo_attribs<VboType::Double, double>
    //{
    //    static const unsigned element_count = 1;
    //    inline static void push(const double &val, std::vector<double> &values)
    //    {
    //        values.push_back(val);
    //    }
    //    inline static bool check_cache(unsigned offset, const double &val, std::vector<double> &values)
    //    {
    //        return (values[offset] == val);
    //    }
    //};
}
