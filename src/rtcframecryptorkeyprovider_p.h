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

#ifndef RTCFRAMECRYPTORKEYPROVIDER_P_H
#define RTCFRAMECRYPTORKEYPROVIDER_P_H

#include <QByteArray>

#include <memory>

#include "rtc_base/ref_count.h"
#include "api/crypto/frame_crypto_transformer.h"

class RTCFrameCryptorKeyProviderPrivate
{
  public:
    explicit RTCFrameCryptorKeyProviderPrivate();
    rtc::scoped_refptr<webrtc::KeyProvider> nativeKeyProvider() const;

    rtc::scoped_refptr<webrtc::DefaultKeyProviderImpl> nativeKeyProvider_;
};

#endif // RTCFRAMECRYPTORKEYPROVIDER_P_H
