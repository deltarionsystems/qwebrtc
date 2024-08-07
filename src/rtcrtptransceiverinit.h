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

#ifndef RTCRTPTRANSCEIVERINIT_H
#define RTCRTPTRANSCEIVERINIT_H

#include <QObject>
#include <QString>
#include <QVector>

#include "rtcrtpencodingparameters.h"
#include "rtctypes.h"

class RTCRtpTransceiverInitPrivate;
/**
 * @brief The RTCRtpTransceiverInit class.
 */
class RTCRtpTransceiverInit : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpTransceiverInit object.
     */
    explicit RTCRtpTransceiverInit(QObject *parent = nullptr);

    /**
     * @brief Gets the direction of the RTCRtpTransceiver.
     * @return The direction.
     */
    RTCRtpTransceiverDirection direction() const;

    /**
     * @brief Sets the direction of the RTCRtpTransceiver.
     * @param direction The direction.
     */
    void setDirection(const RTCRtpTransceiverDirection &direction);

    /**
     * @brief Gets the stream IDs.
     * @return The stream IDs.
     */
    QVector<QString> streamIds() const;

    /**
     * @brief Sets the stream IDs.
     * @param streamIds The stream IDs.
     */
    void setStreamIds(const QVector<QString> &streamIds);

    /**
     * @brief Gets the send encodings.
     * @return The send encodings.
     */
    QVector<RTCRtpEncodingParameters *> sendEncodings() const;

    /**
     * @brief Sets the send encodings.
     * @param sendEncodings The send encodings.
     */
    void setSendEncodings(const QVector<RTCRtpEncodingParameters *> &sendEncodings);

  private:
    RTCRtpTransceiverInitPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpTransceiverInit)

    friend class RTCPeerConnection;
};

#endif // RTCRTPTRANSCEIVERINIT_H
