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

#include "rtcframecryptorkeyprovider.h"
#include "rtcframecryptorkeyprovider_p.h"

RTCFrameCryptorKeyProviderPrivate::RTCFrameCryptorKeyProviderPrivate()
{
}

void RTCFrameCryptorKeyProvider::init(QByteArray salt, int windowSize, bool sharedKeyMode,
                                      QByteArray uncryptedMagicBytes, int failureTolerance,
                                      int keyRingSize, bool discardFrameWhenCryptorNotReady)
{
    d_ptr = new RTCFrameCryptorKeyProviderPrivate();
    webrtc::KeyProviderOptions options;
    options.ratchet_salt =
        std::vector<uint8_t>(reinterpret_cast<const uint8_t *>(salt.data()),
                             reinterpret_cast<const uint8_t *>(salt.data()) + salt.size());
    options.ratchet_window_size = windowSize;
    options.shared_key = sharedKeyMode;
    options.failure_tolerance = failureTolerance;
    options.key_ring_size = keyRingSize;
    options.discard_frame_when_cryptor_not_ready = discardFrameWhenCryptorNotReady;
    if (uncryptedMagicBytes != nullptr)
    {
        options.uncrypted_magic_bytes =
            std::vector<uint8_t>(reinterpret_cast<const uint8_t *>(uncryptedMagicBytes.data()),
                                 reinterpret_cast<const uint8_t *>(uncryptedMagicBytes.data()) +
                                     uncryptedMagicBytes.size());
    }
    d_ptr->nativeKeyProvider_ = rtc::make_ref_counted<webrtc::DefaultKeyProviderImpl>(options);
}

RTCFrameCryptorKeyProvider::RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize,
                                                       bool sharedKeyMode,
                                                       QByteArray uncryptedMagicBytes,
                                                       QObject *parent)
    : QObject{parent}
{
    init(salt, windowSize, sharedKeyMode, uncryptedMagicBytes, -1, webrtc::DEFAULT_KEYRING_SIZE,
         false);
}

RTCFrameCryptorKeyProvider::RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize,
                                                       bool sharedKeyMode,
                                                       QByteArray uncryptedMagicBytes,
                                                       int failureTolerance, int keyRingSize,
                                                       QObject *parent)
    : QObject{parent}
{
    init(salt, windowSize, sharedKeyMode, uncryptedMagicBytes, -1, keyRingSize, false);
}

RTCFrameCryptorKeyProvider::RTCFrameCryptorKeyProvider(
    QByteArray salt, int windowSize, bool sharedKeyMode, QByteArray uncryptedMagicBytes,
    int failureTolerance, int keyRingSize, bool discardFrameWhenCryptorNotReady, QObject *parent)
    : QObject{parent}
{
    init(salt, windowSize, sharedKeyMode, uncryptedMagicBytes, failureTolerance, keyRingSize,
         discardFrameWhenCryptorNotReady);
}

void RTCFrameCryptorKeyProvider::setSharedKey(QByteArray key, int index)
{
    Q_D(RTCFrameCryptorKeyProvider);
    d->nativeKeyProvider_->SetSharedKey(
        index, std::vector<uint8_t>(reinterpret_cast<const uint8_t *>(key.data()),
                                    reinterpret_cast<const uint8_t *>(key.data()) + key.size()));
}

QByteArray RTCFrameCryptorKeyProvider::ratchetSharedKey(int index)
{
    Q_D(RTCFrameCryptorKeyProvider);
    std::vector<uint8_t> nativeKey = d->nativeKeyProvider_->RatchetSharedKey(index);
    return QByteArray((const char *)nativeKey.data(), nativeKey.size());
}

QByteArray RTCFrameCryptorKeyProvider::exportSharedKey(int index)
{
    Q_D(RTCFrameCryptorKeyProvider);
    std::vector<uint8_t> nativeKey = d->nativeKeyProvider_->ExportSharedKey(index);
    return QByteArray(reinterpret_cast<const char *>(nativeKey.data()), nativeKey.size());
}

void RTCFrameCryptorKeyProvider::setKey(QByteArray key, int index, QString participantId)
{
    Q_D(RTCFrameCryptorKeyProvider);
    d->nativeKeyProvider_->SetKey(
        participantId.toStdString(), index,
        std::vector<uint8_t>(reinterpret_cast<const uint8_t *>(key.data()),
                             reinterpret_cast<const uint8_t *>(key.data()) + key.size()));
}

QByteArray RTCFrameCryptorKeyProvider::ratchetKey(QString participantId, int index)
{
    Q_D(RTCFrameCryptorKeyProvider);
    std::vector<uint8_t> nativeKey =
        d->nativeKeyProvider_->RatchetKey(participantId.toStdString(), index);
    return QByteArray(reinterpret_cast<const char *>(nativeKey.data()), nativeKey.size());
}

QByteArray RTCFrameCryptorKeyProvider::exportKey(QString participantId, int index)
{
    Q_D(RTCFrameCryptorKeyProvider);
    std::vector<uint8_t> nativeKey =
        d->nativeKeyProvider_->ExportKey(participantId.toStdString(), index);
    return QByteArray(reinterpret_cast<const char *>(nativeKey.data()), nativeKey.size());
}

void RTCFrameCryptorKeyProvider::setSifTrailer(QByteArray trailer)
{
    Q_D(RTCFrameCryptorKeyProvider);
    d->nativeKeyProvider_->SetSifTrailer(
        std::vector<uint8_t>(reinterpret_cast<const uint8_t *>(trailer.data()),
                             reinterpret_cast<const uint8_t *>(trailer.data()) + trailer.size()));
}
