// #pragma once
#pragma once

#include "i3g4250d.hpp"

namespace application
{

namespace
{

constexpr uint8_t READ_BIT = 0x80;

constexpr uint8_t AUTO_INCREMENT_BIT = 0x40;

} // namespace

template<typename CsPin>
I3g4250d<CsPin>::I3g4250d(
    hardware::Spi& spi
)
    : spi_(spi)
{
    ctx_.write_reg = write_reg;
    ctx_.read_reg  = read_reg;
    ctx_.handle    = this;
}

template<typename CsPin>
bool I3g4250d<CsPin>::init()
{
    uint8_t who_am_i = 0;

    if (!read_device_id(who_am_i))
    {
        return false;
    }

    if (who_am_i != I3G4250D_ID)
    {
        return false;
    }

    if (i3g4250d_data_rate_set(
            &ctx_,
            I3G4250D_ODR_100Hz
        ) != 0)
    {
        return false;
    }

    if (i3g4250d_full_scale_set(
            &ctx_,
            I3G4250D_245dps
        ) != 0)
    {
        return false;
    }

    return true;
}

template<typename CsPin>
bool I3g4250d<CsPin>::read_device_id(
    uint8_t& id
)
{
    return (
        i3g4250d_device_id_get(
            &ctx_,
            &id
        ) == 0
    );
}

template<typename CsPin>
bool I3g4250d<CsPin>::data_ready()
{
    uint8_t ready = 0;

    if (i3g4250d_flag_data_ready_get(
            &ctx_,
            &ready
        ) != 0)
    {
        return false;
    }

    return (ready != 0);
}

template<typename CsPin>
bool I3g4250d<CsPin>::read_angular_rate(
    AngularRate& rate
)
{
    int16_t raw[3] {};

    if (i3g4250d_angular_rate_raw_get(
            &ctx_,
            raw
        ) != 0)
    {
        return false;
    }

    rate.x_dps =
        i3g4250d_from_fs245dps_to_mdps(
            raw[0]
        ) / 1000.0f;

    rate.y_dps =
        i3g4250d_from_fs245dps_to_mdps(
            raw[1]
        ) / 1000.0f;

    rate.z_dps =
        i3g4250d_from_fs245dps_to_mdps(
            raw[2]
        ) / 1000.0f;

    return true;
}

template<typename CsPin>
int32_t I3g4250d<CsPin>::write_reg(
    void* handle,
    uint8_t reg,
    const uint8_t* data,
    uint16_t len
)
{
    auto* self =
        static_cast<I3g4250d*>(handle);

    if (len == 0)
    {
        return -1;
    }

    if (len > 1)
    {
        reg |= AUTO_INCREMENT_BIT;
    }

    CsPin::reset();

    bool ok =
        self->spi_.write(
            &reg,
            1
        );

    if (ok)
    {
        ok = self->spi_.write(
            data,
            len
        );
    }

    CsPin::set();

    return ok ? 0 : -1;
}

template<typename CsPin>
int32_t I3g4250d<CsPin>::read_reg(
    void* handle,
    uint8_t reg,
    uint8_t* data,
    uint16_t len
)
{
    auto* self =
        static_cast<I3g4250d*>(handle);

    if (len == 0)
    {
        return -1;
    }

    reg |= READ_BIT;

    if (len > 1)
    {
        reg |= AUTO_INCREMENT_BIT;
    }

    CsPin::reset();

    bool ok =
        self->spi_.write(
            &reg,
            1
        );

    if (ok)
    {
        ok = self->spi_.read(
            data,
            len
        );
    }

    CsPin::set();

    return ok ? 0 : -1;
}

} // namespace application