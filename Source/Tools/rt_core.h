#ifndef RT_CORE_H
#define RT_CORE_H

#include<inttypes.h>
#include <QGLFunctions>
#include "rt_vector.h"
#include "rt_matrix.h"

namespace vis
{
extern uint32_t s_random_seed;

inline int32_t rand_i(uint32_t& seed)
{
    return ((seed = seed * 214013L + 2531011L) >> 16) & 32767;
}

inline float rand_f(uint32_t& seed)
{
    return (float)rand_i(seed) * (1.0f / 32767.0f);
}


inline float rand_f()
{
    return rand_f(s_random_seed);
}

struct Memory_stream
{
    Memory_stream();
    Memory_stream(void* data, uint32_t size);

    void reset(void* data, uint32_t size);

    uint32_t size() const;
    uint32_t offset() const;

    void seek(uint32_t offset);

    virtual uint32_t read(void *buffer, uint32_t size);
    virtual uint32_t write(const void *buffer, uint32_t size);

    void *data();
    const void *data() const;

    void *offset_data();

    const void *offset_data() const;

    private:
        uint32_t _size;
        uint32_t _offset;
        uint8_t* _data;
    };

////////////////////////////////////////////////////////////////
    inline Memory_stream::Memory_stream()
    {
        _data = 0;
        _size = _offset = 0;
    }

    inline Memory_stream::Memory_stream(void* data, uint32_t size)
    {
        reset(data, size);
    }

    inline void Memory_stream::reset(void* data, uint32_t size)
    {
        _data = (uint8_t*)data;
        _size = size;
        _offset = 0;
    }

    inline void Memory_stream::seek(uint32_t offset)
        {
            _offset = offset;
            if (_offset > _size) {
                _offset = _size;
                //TRACE("WARNING: invalid seek offset!\n");
            }

        }

        inline uint32_t Memory_stream::size() const
        {
            return _size;
        }

        inline uint32_t Memory_stream::offset() const
        {
            return _offset;
        }


        inline const void *Memory_stream::data() const
        {
            return _data;
        }

        inline void *Memory_stream::offset_data()
        {
            return _data + _offset;
        }

        inline const void *Memory_stream::offset_data() const
        {
            return _data + _offset;
        }



struct Render_data
{
    void* meta_data;
    Matrix44_f matrix[2];
};


struct Render_context
{
    uint32_t active_pass;
    uint32_t active_type;
    //Matrix44_f cam;
    Matrix44_f view;
    Matrix44_f proj;
    Matrix44_f view_proj;
    Matrix44_f view_transform;
    //Matrix44_f inf_proj;
    //Matrix44_f inf_view_proj;
    int draw_calls;
};

struct Render_element
{
    uint32_t type_index;
};

}

#endif // RT_CORE_H
