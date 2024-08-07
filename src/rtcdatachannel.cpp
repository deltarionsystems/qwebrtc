// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rtcdatachannel.h"

#include <memory>
#include "rtcdatachannel_p.h"

namespace webrtc
{

DataChannelDelegateAdapter::DataChannelDelegateAdapter(std::shared_ptr<RTCDataChannel> channel)
{
    channel_ = channel;
}

void DataChannelDelegateAdapter::OnStateChange()
{
    auto channel = channel_.lock();
    if (channel)
    {

        Q_EMIT channel->dataChannelDidChangeState();
    }
}

void DataChannelDelegateAdapter::OnMessage(const DataBuffer &buffer)
{
    auto channel = channel_.lock();
    if (channel)
    {
        auto dataBuffer = new RTCDataBufferPrivate(buffer);
        auto bytes =
            QByteArray(reinterpret_cast<const char *>(dataBuffer->nativeDataBuffer_->data.data()),
                       dataBuffer->nativeDataBuffer_->data.size());
        Q_EMIT channel->dataChannelDidReceiveMessageWithBuffer(bytes);
        delete dataBuffer;
    }
}

void DataChannelDelegateAdapter::OnBufferedAmountChange(uint64_t previousAmount)
{
    auto channel = channel_.lock();
    if (channel)
    {
        Q_EMIT channel->dataChannelDidChangeBufferedAmount(previousAmount);
    }
}

} // namespace webrtc

RTCDataChannelPrivate::RTCDataChannelPrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeDataChannel);

    factory_ = factory;
    nativeDataChannel_ = nativeDataChannel;

    observer_ = std::make_unique<webrtc::DataChannelDelegateAdapter>(
        std::shared_ptr<RTCDataChannel>(q_ptr));
}

RTCDataChannelPrivate::~RTCDataChannelPrivate()
{
    nativeDataChannel_->UnregisterObserver();
}

RTCDataChannel::RTCDataChannel(RTCDataChannelPrivate &d, QObject *parent)
    : QObject(parent), d_ptr(&d)
{
    d_ptr->q_ptr = this;
}

QString RTCDataChannel::label() const
{
    Q_D(const RTCDataChannel);
    return QString::fromStdString(d_ptr->nativeDataChannel_->label());
}

bool RTCDataChannel::isReliable() const
{
    Q_D(const RTCDataChannel);
    return d_ptr->nativeDataChannel_->reliable();
}

bool RTCDataChannel::isOrdered() const
{
    return d_ptr->nativeDataChannel_->ordered();
}

unsigned int RTCDataChannel::maxRetransmitTime() const
{
    return d_ptr->maxPacketLifeTime_;
}

unsigned short RTCDataChannel::maxPacketLifeTime() const
{
    return d_ptr->nativeDataChannel_->maxRetransmitTime();
}

unsigned short RTCDataChannel::maxRetransmits() const
{
    return d_ptr->nativeDataChannel_->maxRetransmits();
}

QString RTCDataChannel::protocol() const
{
    return QString::fromStdString(d_ptr->nativeDataChannel_->protocol());
}

bool RTCDataChannel::isNegotiated() const
{
    return d_ptr->nativeDataChannel_->negotiated();
}

int RTCDataChannel::streamId() const
{
    return d_ptr->channelId_;
}

int RTCDataChannel::channelId() const
{
    return d_ptr->nativeDataChannel_->id();
}

RTCDataChannelState RTCDataChannel::readyState() const
{
    return static_cast<RTCDataChannelState>(d_ptr->nativeDataChannel_->state());
}

unsigned long long RTCDataChannel::bufferedAmount() const
{
    return d_ptr->nativeDataChannel_->buffered_amount();
}

void RTCDataChannel::close()
{
    d_ptr->nativeDataChannel_->Close();
}

bool RTCDataChannel::sendData(const RTCDataBuffer *data)
{
    Q_D(RTCDataChannel);
    return d_ptr->nativeDataChannel_->Send(*data->d_ptr->nativeDataBuffer());
}

RTCDataChannel::~RTCDataChannel()
{
    delete d_ptr;
}
