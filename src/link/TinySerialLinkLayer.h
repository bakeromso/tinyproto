/*
    Copyright 2016-2022 (C) Alexey Dynda

    This file is part of Tiny Protocol Library.

    Protocol Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Protocol Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Protocol Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "link/TinyLinkLayer.h"
#include "interface/TinySerial.h"

namespace tinyproto
{

/**
 * Template class for Serial-based communication for any of TinyProto Links
 *
 * @param BASE Base class for protocol type: IFdLinkLayer or IHdlcLinkLayer.
 * @param BSIZE Maximum block size which can be transmitted via Serial Link as single block
 */
template <class BASE, int BSIZE> class ISerialLinkLayer: public BASE
{
public:
    ISerialLinkLayer(char *dev, void *buffer, int size)
        : BASE(buffer, size)
        , m_serial(dev)
    {
    }

    bool begin(on_frame_read_cb_t onReadCb, on_frame_sent_cb_t onSendCb, void *udata) override
    {
        bool result = BASE::begin(onReadCb, onSendCb, udata);
        m_serial.setTimeout(this->getTimeout());
        return result && m_serial.begin(m_speed);
    }

    void end() override
    {
        m_serial.end();
        BASE::end();
    }

    void runRx() override
    {
        uint8_t buf[BSIZE];
        uint8_t *p = buf;

        int len = m_serial.readBytes(p, BSIZE);
        while ( len > 0 )
        {
            int temp = BASE::parseData(p, len);
            if ( temp < 0 )
            {
                break;
            }
            len -= temp;
            p += temp;
        }
    }

    void runTx() override
    {
        uint8_t buf[BSIZE];
        int len = BASE::getData(buf, BSIZE);
        uint8_t *ptr = buf;
        while ( len > 0 )
        {
            int sent = m_serial.write(ptr, len);
            if ( sent < 0 )
            {
                break;
            }
            ptr += sent;
            len -= sent;
        }
    }

    void setSpeed(uint32_t speed)
    {
        m_speed = speed;
    }

private:
    uint32_t m_speed = 115200;
    tinyproto::Serial m_serial;
};

} // namespace tinyproto
