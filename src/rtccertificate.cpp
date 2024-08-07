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

#include "rtccertificate.h"

#include <QtCore/QObject>

#include "rtc_base/logging.h"
#include "rtc_base/rtc_certificate_generator.h"
#include "rtc_base/ssl_identity.h"

RTCCertificate::RTCCertificate(QObject *parent) : QObject(parent)
{
}

RTCCertificate::RTCCertificate(const QString &privateKey, const QString &certificate,
                               QObject *parent)
    : QObject(parent), privateKey_(privateKey), certificate_(certificate)
{
}

QString RTCCertificate::certificate() const
{
    return certificate_;
}

QString RTCCertificate::privateKey() const
{
    return privateKey_;
}

RTCCertificate *RTCCertificate::generateCertificateWithParams(const QMap<QString, QString> &params)
{
    rtc::KeyType keyType = rtc::KT_ECDSA;
    QString keyTypeString = params.find("name").value();
    if (!keyTypeString.isEmpty() && keyTypeString == "RSASSA-PKCS1-v1_5")
    {
        keyType = rtc::KT_RSA;
    }

    QString expires = params.find("expires").value();
    rtc::scoped_refptr<rtc::RTCCertificate> cc_certificate = nullptr;
    if (!expires.isEmpty())
    {
        uint64_t expirationTimestamp = expires.toULongLong();
        cc_certificate = rtc::RTCCertificateGenerator::GenerateCertificate(rtc::KeyParams(keyType),
                                                                           expirationTimestamp);
    }
    else
    {
        cc_certificate = rtc::RTCCertificateGenerator::GenerateCertificate(rtc::KeyParams(keyType),
                                                                           absl::nullopt);
    }
    if (!cc_certificate)
    {
        RTC_LOG(LS_ERROR) << "Failed to generate certificate.";
        return nullptr;
    }

    // grab PEMs and create an NS RTCCerticicate
    rtc::RTCCertificatePEM pem = cc_certificate->ToPEM();
    std::string pem_private_key = pem.private_key();
    std::string pem_certificate = pem.certificate();
    RTC_LOG(LS_INFO) << "CERT PEM ";
    RTC_LOG(LS_INFO) << pem_certificate;

    return new RTCCertificate(QString::fromStdString(pem_private_key),
                              QString::fromStdString(pem_certificate));
}
