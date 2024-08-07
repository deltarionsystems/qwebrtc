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

#ifndef RTCFIELDTRIALS_H
#define RTCFIELDTRIALS_H

#include <QObject>
#include <QString>
#include <QMap>

/**
 * @brief The RTCFieldTrials class.
 */
class RTCFieldTrials : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCFieldTrials object.
     */
    explicit RTCFieldTrials(QObject *parent = nullptr);

    /**
     * @brief Gets the only valid value for the following if set is kRTCFieldTrialEnabledValue.
     * @return The only valid value for the following if set is kRTCFieldTrialEnabledValue.
     */
    static QString RTCFieldTrialAudioForceABWENoTWCCKey();
    static QString RTCFieldTrialFlexFec03AdvertisedKey();
    static QString RTCFieldTrialFlexFec03Key();
    static QString RTCFieldTrialH264HighProfileKey();
    static QString RTCFieldTrialMinimizeResamplingOnMobileKey();
    static QString RTCFieldTrialUseNWPathMonitor();

    /**
     * @brief Gets the valid value for field trials above.
     * @return The valid value for field trials above.
     */
    static QString RTCFieldTrialEnabledValue();

    /**
     * @brief Initialize field trials using a dictionary mapping field trial keys to their values.
     * See above for valid keys and values. Must be called before any other call into WebRTC.
     * See: webrtc/system_wrappers/include/field_trial.h
     * @param fieldTrials The dictionary mapping field trial keys to their values.
     */
    static void RTCInitFieldTrialDictionary(QMap<QString, QString> fieldTrials);
};

#endif // RTCFIELDTRIALS_H
