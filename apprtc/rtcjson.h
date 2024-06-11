#ifndef ARTCICESERVER_H
#define ARTCICESERVER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QVariantMap>

#include "rtciceserver.h"
#include "rtcsessiondescription.h"
#include "rtcicecandidate.h"

// RTCIceServer

static RTCIceServer* fromJson(const QVariantMap &json) {
    QStringList urls = json["urls"].toStringList();
    QString username = json.contains("username") ? json["username"].toString() : "";
    QString credential = json.contains("credential") ? json["credential"].toString() : "";
    return new RTCIceServer(urls, username, credential);
}

// RTCSessionDescription

static RTCSessionDescription* fromJson(const QVariantMap &json) {
    QString typeString = json["type"].toString();
    RTCSdpType type = typeForString(typeString);
    QString sdp = json["sdp"].toString();
    return new RTCSessionDescription(type, sdp);
}

QByteArray toJson() const {
    QVariantMap json = {
        {"type", stringForType(type)},
        {"sdp", sdp}
    };
    QJsonDocument doc = QJsonDocument::fromVariant(json);
    return doc.toJson();
}

// RTCIceCandidate

static RTCIceCandidate* fromJson(const QVariantMap &json) {
    QString mid = json["id"].toString();
    QString sdp = json["candidate"].toString();
    int mLineIndex = json["label"].toInt();
    return new RTCIceCandidate(sdp, mLineIndex, mid);
}

static QByteArray jsonDataForIceCandidates(const QList<RTCIceCandidate*> &candidates, const QString &typeValue) {
    QJsonArray jsonCandidates;
    for (RTCIceCandidate *candidate : candidates) {
        QVariantMap jsonCandidate = candidate->toJson();
        jsonCandidates.append(QJsonObject::fromVariantMap(jsonCandidate));
    }
    QJsonObject json = {
        {"type", typeValue},
        {"candidates", jsonCandidates}
    };
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}

QVariantMap toJson() const {
    return {
        {"id", mid},
        {"label", mLineIndex},
        {"candidate", sdp}
    };
}

static QList<RTCIceCandidate*> candidatesFromJson(const QVariantMap &json) {
    QList<RTCIceCandidate*> candidates;
    QJsonArray jsonCandidates = json["candidates"].toJsonArray();
    for (const QJsonValue &value : jsonCandidates) {
        RTCIceCandidate *candidate = RTCIceCandidate::fromJson(value.toObject().toVariantMap());
        candidates.append(candidate);
    }
    return candidates;
}

QByteArray RTCIceCandidate::toJsonData() const {
    QJsonObject json = {
        {"type", "candidate"},
        {"label", mLineIndex},
        {"id", mid},
        {"candidate", sdp}
    };
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}

QVariantMap RTCIceCandidate::toJson() const {
    return {
        {"label", mLineIndex},
        {"id", mid},
        {"candidate", sdp}
    };
}

#endif // ARTCICESERVER_H
