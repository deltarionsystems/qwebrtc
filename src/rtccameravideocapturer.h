#ifndef RTCCAMERAVIDEOCAPTURER_H
#define RTCCAMERAVIDEOCAPTURER_H

/* Webcamoid, webcam capture application.
 * Copyright (C) 2023  Gonzalo Exequiel Pedone
 *
 * Webcamoid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamoid. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef CAPTUREQT_H
#define CAPTUREQT_H

#include "rtcmediacapturer.h"

class CaptureQtPrivate;

class CaptureQt : public Capture
{
    Q_OBJECT

  public:
    CaptureQt(QObject *parent = nullptr);
    ~CaptureQt();

    Q_INVOKABLE QStringList webcams() const override;
    Q_INVOKABLE QString device() const override;
    Q_INVOKABLE QList<int> streams() override;
    Q_INVOKABLE QList<int> listTracks(AkCaps::CapsType type) override;
    Q_INVOKABLE QString ioMethod() const override;
    Q_INVOKABLE int nBuffers() const override;
    Q_INVOKABLE QString description(const QString &webcam) const override;
    Q_INVOKABLE CaptureVideoCaps caps(const QString &webcam) const override;
    Q_INVOKABLE QVariantList imageControls() const override;
    Q_INVOKABLE bool setImageControls(const QVariantMap &imageControls) override;
    Q_INVOKABLE bool resetImageControls() override;
    Q_INVOKABLE QVariantList cameraControls() const override;
    Q_INVOKABLE bool setCameraControls(const QVariantMap &cameraControls) override;
    Q_INVOKABLE bool resetCameraControls() override;
    Q_INVOKABLE AkPacket readFrame() override;
    Q_INVOKABLE bool isTorchSupported() const override;
    Q_INVOKABLE TorchMode torchMode() const override;

  private:
    CaptureQtPrivate *d;

  public Q_SLOTS:
    bool init() override;
    void uninit() override;
    void setDevice(const QString &device) override;
    void setStreams(const QList<int> &streams) override;
    void setIoMethod(const QString &ioMethod) override;
    void setNBuffers(int nBuffers) override;
    void setTorchMode(TorchMode mode) override;
    void resetDevice() override;
    void resetStreams() override;
    void resetIoMethod() override;
    void resetNBuffers() override;
    void resetTorchMode() override;
    void reset() override;
};

#endif // CAPTUREQT_H

#endif //RTCCAMERAVIDEOCAPTURER_H
