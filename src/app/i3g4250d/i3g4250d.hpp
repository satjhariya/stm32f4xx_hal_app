#pragma once

#include <cstdint>

#include "spi.hpp"
#include "i3g4250d_reg.h"

namespace application
{

template<typename CsPin>
class I3g4250d
{
public:
    struct AngularRate
    {
        float x_dps;
        float y_dps;
        float z_dps;
    };

public:
    explicit I3g4250d(
        hardware::Spi& spi
    );

    bool init();

    bool read_device_id(
        uint8_t& id
    );

    bool data_ready();

    bool read_angular_rate(
        AngularRate& rate
    );

private:
    static int32_t write_reg(
        void* handle,
        uint8_t reg,
        const uint8_t* data,
        uint16_t len
    );

    static int32_t read_reg(
        void* handle,
        uint8_t reg,
        uint8_t* data,
        uint16_t len
    );

private:
    hardware::Spi& spi_;

    stmdev_ctx_t ctx_ {};
};

} // namespace application

#include "i3g4250d.tpp"