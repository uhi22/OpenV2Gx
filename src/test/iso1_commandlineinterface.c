

/*********************************************************************************************************
*  Decoder --> JSON
**********************************************************************************************************
*********************************************************************************************************/

void translateIso1HeaderToJson(void) {
    char sTmp[40], s2[30];
    int i, n;
    #define h iso1Doc.V2G_Message.Header
    n = h.SessionID.bytesLen;
    //sprintf(sTmp, "%d", n); addProperty("header.SessionID.byteLen", sTmp);
    strcpy(sTmp,"");
    for (i=0; (i<n)&&(i<30); i++) {
            sprintf(s2, "%02x", h.SessionID.bytes[i]);
            strcat(sTmp, s2);
    }
    addProperty("header.SessionID", sTmp);
    sprintf(sTmp, "%d", h.Notification_isUsed); addProperty("header.Notification_isUsed", sTmp);
    sprintf(sTmp, "%d", h.Signature_isUsed); addProperty("header.Signature_isUsed", sTmp);
    #undef h
}

void translateIso1UnitToJson(char *property, int unit) {
    /* Hint: Units are mandatory for ISO1 */
    char sTmp[40];
    strcpy(sTmp, "UNKNOWN_UNIT");
    switch (unit) {
        case iso1unitSymbolType_h: strcpy(sTmp, "h"); break;
        case iso1unitSymbolType_m: strcpy(sTmp, "m"); break;
        case iso1unitSymbolType_s: strcpy(sTmp, "s"); break;
        case iso1unitSymbolType_A: strcpy(sTmp, "A"); break;
        case iso1unitSymbolType_V: strcpy(sTmp, "V"); break;
        case iso1unitSymbolType_W: strcpy(sTmp, "W"); break;
        case iso1unitSymbolType_Wh: strcpy(sTmp, "Wh"); break;
    }
    addProperty(property, sTmp);
}

void translateIso1ResponseCodeToJson(iso1responseCodeType rc) {
    char sLoc[40];
    strcpy(sLoc, "UNKNOWN_ERROR_CODE");
    switch (rc) {
        case iso1responseCodeType_OK: strcpy(sLoc, "OK"); break;
        case iso1responseCodeType_OK_NewSessionEstablished: strcpy(sLoc, "OK_NewSessionEstablished"); break;
        case iso1responseCodeType_OK_OldSessionJoined: strcpy(sLoc, "OK_OldSessionJoined"); break;
        case iso1responseCodeType_OK_CertificateExpiresSoon: strcpy(sLoc, "OK_CertificateExpiresSoon"); break;
        case iso1responseCodeType_FAILED: strcpy(sLoc, "FAILED"); break;
        case iso1responseCodeType_FAILED_SequenceError: strcpy(sLoc, "FAILED_SequenceError"); break;
        case iso1responseCodeType_FAILED_ServiceIDInvalid: strcpy(sLoc, "FAILED_ServiceIDInvalid"); break;
        case iso1responseCodeType_FAILED_UnknownSession: strcpy(sLoc, "FAILED_UnknownSession"); break;
        case iso1responseCodeType_FAILED_ServiceSelectionInvalid: strcpy(sLoc, "FAILED_ServiceSelectionInvalid"); break;
        case iso1responseCodeType_FAILED_PaymentSelectionInvalid: strcpy(sLoc, "FAILED_PaymentSelectionInvalid"); break;
        case iso1responseCodeType_FAILED_CertificateExpired: strcpy(sLoc, "FAILED_CertificateExpired"); break;
        case iso1responseCodeType_FAILED_SignatureError: strcpy(sLoc, "FAILED_SignatureError"); break;
        case iso1responseCodeType_FAILED_NoCertificateAvailable: strcpy(sLoc, "FAILED_NoCertificateAvailable"); break;
        case iso1responseCodeType_FAILED_CertChainError: strcpy(sLoc, "FAILED_CertChainError"); break;
        case iso1responseCodeType_FAILED_ChallengeInvalid: strcpy(sLoc, "FAILED_ChallengeInvalid"); break;
        case iso1responseCodeType_FAILED_ContractCanceled: strcpy(sLoc, "FAILED_ContractCanceled"); break;
        case iso1responseCodeType_FAILED_WrongChargeParameter: strcpy(sLoc, "FAILED_WrongChargeParameter"); break;
        case iso1responseCodeType_FAILED_PowerDeliveryNotApplied: strcpy(sLoc, "FAILED_PowerDeliveryNotApplied"); break;
        case iso1responseCodeType_FAILED_TariffSelectionInvalid: strcpy(sLoc, "FAILED_TariffSelectionInvalid"); break;
        case iso1responseCodeType_FAILED_ChargingProfileInvalid: strcpy(sLoc, "FAILED_ChargingProfileInvalid"); break;
        case iso1responseCodeType_FAILED_MeteringSignatureNotValid: strcpy(sLoc, "FAILED_MeteringSignatureNotValid"); break;
        case iso1responseCodeType_FAILED_WrongEnergyTransferMode: strcpy(sLoc, "FAILED_WrongEnergyTransferMode"); break;
        case iso1responseCodeType_FAILED_NoChargeServiceSelected: strcpy(sLoc, "FAILED_NoChargeServiceSelected"); break;
        case iso1responseCodeType_FAILED_ContactorError: strcpy(sLoc, "FAILED_ContactorError"); break;
        case iso1responseCodeType_FAILED_CertificateNotAllowedAtThisEVSE: strcpy(sLoc, "FAILED_CertificateNotAllowedAtThisEVSE"); break;
        case iso1responseCodeType_FAILED_CertificateRevoked: strcpy(sLoc, "FAILED_CertificateRevoked"); break;
    }
    addProperty("ResponseCode", sLoc);
}

void translateiso1DC_EVSEStatusCodeTypeToJson(iso1DC_EVSEStatusCodeType st) {
    char sLoc[40];
    strcpy(sLoc, "UNKNOWN_STATUS");
    switch (st) {
        case iso1DC_EVSEStatusCodeType_EVSE_NotReady: strcpy(sLoc, "EVSE_NotReady"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_Ready: strcpy(sLoc, "EVSE_Ready"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_Shutdown: strcpy(sLoc, "EVSE_Shutdown"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_UtilityInterruptEvent: strcpy(sLoc, "EVSE_UtilityInterruptEvent"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_IsolationMonitoringActive: strcpy(sLoc, "EVSE_IsolationMonitoringActive"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_EmergencyShutdown: strcpy(sLoc, "EVSE_EmergencyShutdown"); break;
        case iso1DC_EVSEStatusCodeType_EVSE_Malfunction: strcpy(sLoc, "EVSE_Malfunction"); break;
        default: strcpy(sLoc, "UNKNOWN_STATUS");
    }
    addProperty("EVSEStatusCode_text", sLoc);
}

void translateiso1DC_EVErrorCodeTypeToJson(iso1DC_EVErrorCodeType e) {
    char sLoc[40];
    strcpy(sLoc, "UNKNOWN_ERROR");
    switch (e) {
        case iso1DC_EVErrorCodeType_NO_ERROR: strcpy(sLoc, "NO_ERROR"); break;
        
        case iso1DC_EVErrorCodeType_FAILED_RESSTemperatureInhibit: strcpy(sLoc, "FAILED_RESSTemperatureInhibit"); break;
        case iso1DC_EVErrorCodeType_FAILED_EVShiftPosition: strcpy(sLoc, "FAILED_EVShiftPosition"); break;
        case iso1DC_EVErrorCodeType_FAILED_ChargerConnectorLockFault: strcpy(sLoc, "FAILED_ChargerConnectorLockFault"); break;
        case iso1DC_EVErrorCodeType_FAILED_EVRESSMalfunction: strcpy(sLoc, "FAILED_EVRESSMalfunction"); break;
        case iso1DC_EVErrorCodeType_FAILED_ChargingCurrentdifferential: strcpy(sLoc, "FAILED_ChargingCurrentdifferential"); break;
        case iso1DC_EVErrorCodeType_FAILED_ChargingVoltageOutOfRange: strcpy(sLoc, "FAILED_ChargingVoltageOutOfRange"); break;
        case iso1DC_EVErrorCodeType_Reserved_A: strcpy(sLoc, "Reserved_A"); break;
        case iso1DC_EVErrorCodeType_Reserved_B: strcpy(sLoc, "Reserved_B"); break;
        case iso1DC_EVErrorCodeType_Reserved_C: strcpy(sLoc, "Reserved_C"); break;
        case iso1DC_EVErrorCodeType_FAILED_ChargingSystemIncompatibility: strcpy(sLoc, "FAILED_ChargingSystemIncompatibility"); break;
        case iso1DC_EVErrorCodeType_NoData: strcpy(sLoc, "NoData"); break;
        default: strcpy(sLoc, "UNKNOWN_ERROR");
    }
    addProperty("DC_EVErrorCodeText", sLoc);
}

/* translate the struct iso1Doc into JSON, to have it ready to give it over stdout to the caller application. */
void translateDocIso1ToJson(void) {
    char sTmp[30];
    char s2[30];
    int i,n;
    initProperties();
    addProperty("schema", "ISO1");
    sprintf(sTmp, "%d", g_errn);
    addProperty("g_errn", sTmp);
    
    translateIso1HeaderToJson();
    if (iso1Doc.V2G_Message.Body.SessionSetupReq_isUsed) {
        addMessageName("SessionSetupReq");
        n=iso1Doc.V2G_Message.Body.SessionSetupReq.EVCCID.bytesLen;
        sprintf(sTmp, "%d", n); addProperty("EVCCID.bytesLen", sTmp);
        strcpy(sTmp,"");
        for (i=0; (i<n)&&(i<20); i++) {
            /* this is no ASCII, at least not at the Ioniq. Show just Hex. */
            sprintf(s2, "%02x", iso1Doc.V2G_Message.Body.SessionSetupReq.EVCCID.bytes[i]);
            strcat(sTmp, s2);
        }
        addProperty("EVCCID", sTmp);
    }
    if (iso1Doc.V2G_Message.Body.SessionSetupRes_isUsed) {
        addMessageName("SessionSetupRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.SessionSetupRes.ResponseCode);
        n=iso1Doc.V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen;
        sprintf(sTmp, "%d", n); addProperty("EVSEID.charactersLen", sTmp);
        strcpy(sTmp,"");
        for (i=0; (i<n)&&(i<20); i++) {
            /* this is no ASCII, at least not at the Ioniq. Show just Hex. */
            sprintf(s2, "%02x", iso1Doc.V2G_Message.Body.SessionSetupRes.EVSEID.characters[i]);
            strcat(sTmp, s2);
        }
        addProperty("EVSEID", sTmp);
        
    }
    if (iso1Doc.V2G_Message.Body.ServiceDiscoveryReq_isUsed) {
        addMessageName("ServiceDiscoveryReq");
        #define m iso1Doc.V2G_Message.Body.ServiceDiscoveryReq
        if (m.ServiceScope_isUsed) {
            addProperty("ServiceScope_isUsed", "True");
            n = m.ServiceScope.charactersLen;
            sprintf(sTmp, "%d", n); addProperty("ServiceScope.charactersLen", sTmp);
        }
        if (m.ServiceCategory_isUsed) {
            addProperty("ServiceCategory_isUsed", "True");
        }
        #undef m
    }
    if (iso1Doc.V2G_Message.Body.ServiceDiscoveryRes_isUsed) {
        addMessageName("ServiceDiscoveryRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.ServiceDiscoveryRes.ResponseCode);
    }

    if (iso1Doc.V2G_Message.Body.PaymentServiceSelectionReq_isUsed) {
        addMessageName("PaymentServiceSelectionReq");
        #define m iso1Doc.V2G_Message.Body.PaymentServiceSelectionReq
        if (m.SelectedPaymentOption==iso1paymentOptionType_Contract) { addProperty("SelectedPaymentOption", "Contract"); }
        if (m.SelectedPaymentOption==iso1paymentOptionType_ExternalPayment) { addProperty("SelectedPaymentOption", "ExternalPayment"); }
        
        n = m.SelectedServiceList.SelectedService.arrayLen;
        sprintf(sTmp, "%d", n); addProperty("SelectedService.arrayLen", sTmp);
        for (i=0; i<n; i++) {
            sprintf(sTmp, "%d:%d", i, m.SelectedServiceList.SelectedService.array[i].ServiceID); addProperty("SelectedService.array", sTmp);
        }
        // ParameterSetID_isUsed
        // ParameterSetID
        #undef m        
    }
    if (iso1Doc.V2G_Message.Body.PaymentServiceSelectionRes_isUsed) {
        addMessageName("PaymentServiceSelectionRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.PaymentServiceSelectionRes.ResponseCode);
    }
    if (iso1Doc.V2G_Message.Body.AuthorizationReq_isUsed) {
        addMessageName("AuthorizationReq");
    }
    if (iso1Doc.V2G_Message.Body.AuthorizationRes_isUsed) {
        addMessageName("AuthorizationRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.AuthorizationRes.ResponseCode);
        #define processing iso1Doc.V2G_Message.Body.AuthorizationRes.EVSEProcessing
        if (processing==iso1EVSEProcessingType_Finished) {
            addProperty("EVSEProcessing", "Finished");
        }
        if (processing==iso1EVSEProcessingType_Ongoing) {
            addProperty("EVSEProcessing", "Ongoing");
        }
        #undef processing
    }
    
    if (iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed) {
        addMessageName("ChargeParameterDiscoveryReq");
        #define m iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryReq
        sprintf(sTmp, "%d", m.RequestedEnergyTransferMode); addProperty("RequestedEnergyTransferMode", sTmp);
        
        sprintf(sTmp, "%d", m.EVChargeParameter_isUsed); addProperty("EVChargeParameter_isUsed", sTmp);
        if (m.EVChargeParameter_isUsed) {
            /* no content */
        }
        sprintf(sTmp, "%d", m.DC_EVChargeParameter_isUsed); addProperty("DC_EVChargeParameter_isUsed", sTmp);
        if (m.DC_EVChargeParameter_isUsed) {
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.DC_EVStatus.EVErrorCode); addProperty("EVErrorCode", sTmp);
            translateiso1DC_EVErrorCodeTypeToJson(m.DC_EVChargeParameter.DC_EVStatus.EVErrorCode);

            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumCurrentLimit.Value); addProperty("EVMaximumCurrentLimit.Value", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumCurrentLimit.Multiplier); addProperty("EVMaximumCurrentLimit.Multiplier", sTmp);
            //sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumCurrentLimit.Unit_isUsed); addProperty("EVMaximumCurrentLimit.Unit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumCurrentLimit.Unit); addProperty("EVMaximumCurrentLimit.Unit", sTmp);
            
            
            
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumPowerLimit_isUsed); addProperty("EVMaximumPowerLimit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumPowerLimit.Value); addProperty("EVMaximumPowerLimit.Value", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumPowerLimit.Multiplier); addProperty("EVMaximumPowerLimit.Multiplier", sTmp);
            //sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumPowerLimit.Unit_isUsed); addProperty("EVMaximumPowerLimit.Unit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumPowerLimit.Unit); addProperty("EVMaximumPowerLimit.Unit", sTmp);
            
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumVoltageLimit.Value); addProperty("EVMaximumVoltageLimit.Value", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumVoltageLimit.Multiplier); addProperty("EVMaximumVoltageLimit.Multiplier", sTmp);
            //sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumVoltageLimit.Unit_isUsed); addProperty("EVMaximumVoltageLimit.Unit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVMaximumVoltageLimit.Unit); addProperty("EVMaximumVoltageLimit.Unit", sTmp);
            
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyCapacity_isUsed); addProperty("EVEnergyCapacity_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyCapacity.Value); addProperty("EVEnergyCapacity.Value", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyCapacity.Multiplier); addProperty("EVEnergyCapacity.Multiplier", sTmp);
            //sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyCapacity.Unit_isUsed); addProperty("EVEnergyCapacity.Unit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyCapacity.Unit); addProperty("EVEnergyCapacity.Unit", sTmp);
            
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyRequest_isUsed); addProperty("EVEnergyRequest_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyRequest.Value); addProperty("EVEnergyRequest.Value", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyRequest.Multiplier); addProperty("EVEnergyRequest.Multiplier", sTmp);
            //sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyRequest.Unit_isUsed); addProperty("EVEnergyRequest.Unit_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.EVEnergyRequest.Unit); addProperty("EVEnergyRequest.Unit", sTmp);

            sprintf(sTmp, "%d", m.DC_EVChargeParameter.FullSOC_isUsed); addProperty("FullSOC_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.FullSOC); addProperty("FullSOC", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.BulkSOC_isUsed); addProperty("BulkSOC_isUsed", sTmp);
            sprintf(sTmp, "%d", m.DC_EVChargeParameter.BulkSOC); addProperty("BulkSOC", sTmp);
        }
        #undef m
    }
    if (iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed) {
        addMessageName("ChargeParameterDiscoveryRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes.ResponseCode);
        #define processing iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEProcessing
        if (processing==iso1EVSEProcessingType_Finished) {
            addProperty("EVSEProcessing", "Finished");
        }
        if (processing==iso1EVSEProcessingType_Ongoing) {
            addProperty("EVSEProcessing", "Ongoing");
        }
        #undef processing
        // todo maybe: EVSEChargeParameter_isUsed
        // todo for AC: AC_EVSEChargeParameter_isUsed
        #define res iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes
        sprintf(sTmp, "%d", res.SAScheduleList_isUsed); addProperty("SAScheduleList_isUsed", sTmp);
        if (res.SAScheduleList_isUsed) {
            sprintf(sTmp, "%d", res.SAScheduleList.SAScheduleTuple.arrayLen); addProperty("SAScheduleList.SAScheduleTuple.arrayLen", sTmp);
            if (res.SAScheduleList.SAScheduleTuple.arrayLen>0) {
                #define SchedTuple0 res.SAScheduleList.SAScheduleTuple.array[0]
                sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.arrayLen); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.arrayLen", sTmp);
                if (SchedTuple0.PMaxSchedule.PMaxScheduleEntry.arrayLen>0) {
                    sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].TimeInterval_isUsed); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].TimeInterval_isUsed", sTmp);
                    sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval_isUsed); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval_isUsed", sTmp);
                    if (SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval_isUsed) {
                        sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.start); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.start", sTmp);
                        sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration_isUsed); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration_isUsed", sTmp);
                        if (SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration_isUsed) {
                            sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration", sTmp);
                        }
                    }
                    sprintf(sTmp, "%d", SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].PMax.Value); addProperty("SchedTuple0.PMaxSchedule.PMaxScheduleEntry.array[0].PMax", sTmp);
                    /* todo: show the complete content of the schedule */
                }
                #undef SchedTuple0
            }
        }
        #undef res
        if (iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed) {
            //DC_EVSEChargeParameter
            //  DC_EVSEStatus
            #define cp iso1Doc.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter
            #define v1 cp.DC_EVSEStatus.EVSEIsolationStatus
            #define v2 cp.DC_EVSEStatus.EVSEIsolationStatus_isUsed
            #define v3 cp.DC_EVSEStatus.EVSEStatusCode
            #define v4 cp.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
            #define v5 cp.DC_EVSEStatus.EVSENotification
            sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
            sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
            sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
            translateiso1DC_EVSEStatusCodeTypeToJson(v3);
            sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
            sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
            #undef v1
            #undef v2
            #undef v3
            #undef v4
            #undef v5
            //  EVSEMaximumCurrentLimit
            sprintf(sTmp, "%d", cp.EVSEMaximumCurrentLimit.Multiplier); addProperty("EVSEMaximumCurrentLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", cp.EVSEMaximumCurrentLimit.Value); addProperty("EVSEMaximumCurrentLimit.Value", sTmp);            
            translateIso1UnitToJson("EVSEMaximumCurrentLimit.Unit", cp.EVSEMaximumCurrentLimit.Unit);
            
            //  EVSEMaximumPowerLimit
            sprintf(sTmp, "%d", cp.EVSEMaximumPowerLimit.Multiplier); addProperty("EVSEMaximumPowerLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", cp.EVSEMaximumPowerLimit.Value); addProperty("EVSEMaximumPowerLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMaximumPowerLimit.Unit", cp.EVSEMaximumPowerLimit.Unit);

            //  EVSEMaximumVoltageLimit
            sprintf(sTmp, "%d", cp.EVSEMaximumVoltageLimit.Multiplier); addProperty("EVSEMaximumVoltageLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", cp.EVSEMaximumVoltageLimit.Value); addProperty("EVSEMaximumVoltageLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMaximumVoltageLimit.Unit", cp.EVSEMaximumVoltageLimit.Unit);
            //  EVSEMinimumCurrentLimit
            sprintf(sTmp, "%d", cp.EVSEMinimumCurrentLimit.Multiplier); addProperty("EVSEMinimumCurrentLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", cp.EVSEMinimumCurrentLimit.Value); addProperty("EVSEMinimumCurrentLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMinimumCurrentLimit.Unit", cp.EVSEMinimumCurrentLimit.Unit);
            //  EVSEMinimumVoltageLimit
            sprintf(sTmp, "%d", cp.EVSEMinimumVoltageLimit.Multiplier); addProperty("EVSEMinimumVoltageLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", cp.EVSEMinimumVoltageLimit.Value); addProperty("EVSEMinimumVoltageLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMinimumVoltageLimit.Unit", cp.EVSEMinimumVoltageLimit.Unit);
            //  EVSECurrentRegulationTolerance
            //  EVSECurrentRegulationTolerance_isUsed
            //  EVSEPeakCurrentRipple
            //  EVSEEnergyToBeDelivered
            //  EVSEEnergyToBeDelivered_isUsed
            //xxx
            #undef cp
        }
    }
    
    if (iso1Doc.V2G_Message.Body.CableCheckReq_isUsed) {
        addMessageName("CableCheckReq");
        #define m iso1Doc.V2G_Message.Body.CableCheckReq
        sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
        #undef m
    }
    if (iso1Doc.V2G_Message.Body.CableCheckRes_isUsed) {
        addMessageName("CableCheckRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.CableCheckRes.ResponseCode);
        #define m iso1Doc.V2G_Message.Body.CableCheckRes
        #define v1 m.DC_EVSEStatus.EVSEIsolationStatus
        #define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
        #define v3 m.DC_EVSEStatus.EVSEStatusCode
        #define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
        #define v5 m.DC_EVSEStatus.EVSENotification
        sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
        sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
        sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
        translateiso1DC_EVSEStatusCodeTypeToJson(v3);
        sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
        sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
        #undef v1
        #undef v2
        #undef v3
        #undef v4
        #undef v5
        if (m.EVSEProcessing==iso1EVSEProcessingType_Finished) {
            addProperty("EVSEProcessing", "Finished");
        }
        if (m.EVSEProcessing==iso1EVSEProcessingType_Ongoing) {
            addProperty("EVSEProcessing", "Ongoing");
        }        
        #undef m
    }

    if (iso1Doc.V2G_Message.Body.PreChargeReq_isUsed) {
        addMessageName("PreChargeReq");
        #define m iso1Doc.V2G_Message.Body.PreChargeReq
        sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
        translateiso1DC_EVErrorCodeTypeToJson(m.DC_EVStatus.EVErrorCode);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);

        sprintf(sTmp, "%d", m.EVTargetVoltage.Multiplier); addProperty("EVTargetVoltage.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVTargetVoltage.Value); addProperty("EVTargetVoltage.Value", sTmp);
        translateIso1UnitToJson("EVTargetVoltage.Unit", m.EVTargetVoltage.Unit);
                        
        sprintf(sTmp, "%d", m.EVTargetCurrent.Multiplier); addProperty("EVTargetCurrent.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVTargetCurrent.Value); addProperty("EVTargetCurrent.Value", sTmp);
        translateIso1UnitToJson("EVTargetCurrent.Unit", m.EVTargetCurrent.Unit);

        #undef m
    }
    if (iso1Doc.V2G_Message.Body.PreChargeRes_isUsed) {
        addMessageName("PreChargeRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.PreChargeRes.ResponseCode);
        #define m iso1Doc.V2G_Message.Body.PreChargeRes
        #define v1 m.DC_EVSEStatus.EVSEIsolationStatus
        #define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
        #define v3 m.DC_EVSEStatus.EVSEStatusCode
        #define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
        #define v5 m.DC_EVSEStatus.EVSENotification
        sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
        sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
        sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
        translateiso1DC_EVSEStatusCodeTypeToJson(v3);
        sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
        sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
        
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
        translateIso1UnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); /* why is this shown as 0? Because unit is optional, see question2. */

        #undef v1
        #undef v2
        #undef v3
        #undef v4
        #undef v5
        #undef m
    }
    if (iso1Doc.V2G_Message.Body.PowerDeliveryReq_isUsed) {
        addMessageName("PowerDeliveryReq");
        sprintf(sTmp, "%d", iso1Doc.V2G_Message.Body.PowerDeliveryReq.ChargeProgress); addProperty("ChargeProgress", sTmp);

        if (iso1Doc.V2G_Message.Body.PowerDeliveryReq.ChargeProgress==0) { addProperty("ChargeProgress_Text", "0"); }
        if (iso1Doc.V2G_Message.Body.PowerDeliveryReq.ChargeProgress==1) { addProperty("ChargeProgress_Text", "1"); }
        /*if (iso1Doc.V2G_Message.Body.PowerDeliveryReq.ChargeProgress==2) { addProperty("ChargeProgress", "2"); } */
        
        sprintf(sTmp, "%d", iso1Doc.V2G_Message.Body.PowerDeliveryReq.ChargingProfile_isUsed); addProperty("ChargingProfile_isUsed", sTmp);
        sprintf(sTmp, "%d", iso1Doc.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter_isUsed); addProperty("EVPowerDeliveryParameter_isUsed", sTmp);
        sprintf(sTmp, "%d", iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed); addProperty("DC_EVPowerDeliveryParameter_isUsed", sTmp);
        if (iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed) {
            #define v1 iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVReady
            #define v2 iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVErrorCode
            #define v3 iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.DC_EVStatus.EVRESSSOC
            #define v4 iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.BulkChargingComplete
            #define v4used iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.BulkChargingComplete_isUsed
            #define v5 iso1Doc.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter.ChargingComplete

            sprintf(sTmp, "%d", v1); addProperty("EVReady", sTmp);
            sprintf(sTmp, "%d", v2); addProperty("EVErrorCode", sTmp);
            translateiso1DC_EVErrorCodeTypeToJson(v2);
            
            sprintf(sTmp, "%d", v3); addProperty("EVRESSSOC", sTmp);
            sprintf(sTmp, "%d", v4used); addProperty("BulkChargingComplete_isUsed", sTmp);
            if (v4used) {
              sprintf(sTmp, "%d", v4); addProperty("BulkChargingComplete", sTmp);
            }
            sprintf(sTmp, "%d", v5); addProperty("ChargingComplete", sTmp);

            #undef v1
            #undef v2
            #undef v3
            #undef v4
            #undef v4used
            #undef v5
        }

    }
    if (iso1Doc.V2G_Message.Body.PowerDeliveryRes_isUsed) {
        addMessageName("PowerDeliveryRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.PowerDeliveryRes.ResponseCode);
        #define m iso1Doc.V2G_Message.Body.PowerDeliveryRes
        if (m.DC_EVSEStatus_isUsed) {
            
            #define v1 m.DC_EVSEStatus.EVSEIsolationStatus
            #define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
            #define v3 m.DC_EVSEStatus.EVSEStatusCode
            #define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
            #define v5 m.DC_EVSEStatus.EVSENotification
            sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
            sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
            sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
            translateiso1DC_EVSEStatusCodeTypeToJson(v3);
            sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
            sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
            #undef m
            #undef v1
            #undef v2
            #undef v3
            #undef v4
            #undef v5
        }
    }

    if (iso1Doc.V2G_Message.Body.CurrentDemandReq_isUsed) {
        addMessageName("CurrentDemandReq");
        #define m iso1Doc.V2G_Message.Body.CurrentDemandReq
        sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
        translateiso1DC_EVErrorCodeTypeToJson(m.DC_EVStatus.EVErrorCode);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);

        sprintf(sTmp, "%d", m.EVTargetCurrent.Multiplier); addProperty("EVTargetCurrent.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVTargetCurrent.Value); addProperty("EVTargetCurrent.Value", sTmp);
        translateIso1UnitToJson("EVTargetCurrent.Unit", m.EVTargetCurrent.Unit);

        sprintf(sTmp, "%d", m.EVMaximumVoltageLimit_isUsed); addProperty("EVMaximumVoltageLimit_isUsed", sTmp);
        if (m.EVMaximumVoltageLimit_isUsed) {
          sprintf(sTmp, "%d", m.EVMaximumVoltageLimit.Multiplier); addProperty("EVMaximumVoltageLimit.Multiplier", sTmp);
          sprintf(sTmp, "%d", m.EVMaximumVoltageLimit.Value); addProperty("EVMaximumVoltageLimit.Value", sTmp);
          translateIso1UnitToJson("EVMaximumVoltageLimit.Unit", m.EVMaximumVoltageLimit.Unit);
        }

        sprintf(sTmp, "%d", m.EVMaximumCurrentLimit_isUsed); addProperty("EVMaximumCurrentLimit_isUsed", sTmp);
        if (m.EVMaximumCurrentLimit_isUsed) {
          sprintf(sTmp, "%d", m.EVMaximumCurrentLimit.Multiplier); addProperty("EVMaximumCurrentLimit.Multiplier", sTmp);
          sprintf(sTmp, "%d", m.EVMaximumCurrentLimit.Value); addProperty("EVMaximumCurrentLimit.Value", sTmp);
          translateIso1UnitToJson("EVMaximumCurrentLimit.Unit", m.EVMaximumCurrentLimit.Unit);
        }
        
        sprintf(sTmp, "%d", m.EVMaximumPowerLimit_isUsed); addProperty("EVMaximumPowerLimit_isUsed", sTmp);
        if (m.EVMaximumPowerLimit_isUsed) {
          sprintf(sTmp, "%d", m.EVMaximumPowerLimit.Multiplier); addProperty("EVMaximumPowerLimit.Multiplier", sTmp);
          sprintf(sTmp, "%d", m.EVMaximumPowerLimit.Value); addProperty("EVMaximumPowerLimit.Value", sTmp);
          translateIso1UnitToJson("EVMaximumPowerLimit.Unit", m.EVMaximumPowerLimit.Unit); 
        }
        
        //m.BulkChargingComplete_isUsed
        //m.BulkChargingComplete
        sprintf(sTmp, "%d", m.ChargingComplete); addProperty("ChargingComplete", sTmp);

        sprintf(sTmp, "%d", m.EVTargetVoltage.Multiplier); addProperty("EVTargetVoltage.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVTargetVoltage.Value); addProperty("EVTargetVoltage.Value", sTmp);
        translateIso1UnitToJson("EVTargetVoltage.Unit", m.EVTargetVoltage.Unit); 
        #undef m
    }
    
    if (iso1Doc.V2G_Message.Body.CurrentDemandRes_isUsed) {
        addMessageName("CurrentDemandRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.CurrentDemandRes.ResponseCode);
        #define m iso1Doc.V2G_Message.Body.CurrentDemandRes
            #define v1 m.DC_EVSEStatus.EVSEIsolationStatus
            #define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
            #define v3 m.DC_EVSEStatus.EVSEStatusCode
            #define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
            #define v5 m.DC_EVSEStatus.EVSENotification
            sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
            sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
            sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
            translateiso1DC_EVSEStatusCodeTypeToJson(v3);
            sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
            sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
            #undef v1
            #undef v2
            #undef v3
            #undef v4
            #undef v5
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
        translateIso1UnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); 

        sprintf(sTmp, "%d", m.EVSEPresentCurrent.Multiplier); addProperty("EVSEPresentCurrent.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVSEPresentCurrent.Value); addProperty("EVSEPresentCurrent.Value", sTmp);
        translateIso1UnitToJson("EVSEPresentCurrent.Unit", m.EVSEPresentCurrent.Unit); 

        sprintf(sTmp, "%d", m.EVSECurrentLimitAchieved); addProperty("EVSECurrentLimitAchieved", sTmp);
        sprintf(sTmp, "%d", m.EVSEVoltageLimitAchieved); addProperty("EVSEVoltageLimitAchieved", sTmp);
        sprintf(sTmp, "%d", m.EVSEPowerLimitAchieved); addProperty("EVSEPowerLimitAchieved", sTmp);

        sprintf(sTmp, "%d", m.EVSEMaximumVoltageLimit.Multiplier); addProperty("EVSEMaximumVoltageLimit.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVSEMaximumVoltageLimit.Value); addProperty("EVSEMaximumVoltageLimit.Value", sTmp);
        translateIso1UnitToJson("EVSEMaximumVoltageLimit.Unit", m.EVSEMaximumVoltageLimit.Unit); 

        if (m.EVSEMaximumCurrentLimit_isUsed) {
            sprintf(sTmp, "%d", m.EVSEMaximumCurrentLimit.Multiplier); addProperty("EVSEMaximumCurrentLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", m.EVSEMaximumCurrentLimit.Value); addProperty("EVSEMaximumCurrentLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMaximumCurrentLimit.Unit", m.EVSEMaximumCurrentLimit.Unit); 
        }
        if (m.EVSEMaximumPowerLimit_isUsed) {
            sprintf(sTmp, "%d", m.EVSEMaximumPowerLimit.Multiplier); addProperty("EVSEMaximumPowerLimit.Multiplier", sTmp);
            sprintf(sTmp, "%d", m.EVSEMaximumPowerLimit.Value); addProperty("EVSEMaximumPowerLimit.Value", sTmp);
            translateIso1UnitToJson("EVSEMaximumPowerLimit.Unit", m.EVSEMaximumPowerLimit.Unit); 
        }
        #undef m
    }
    
    if (iso1Doc.V2G_Message.Body.SessionStopReq_isUsed) {
        addMessageName("SessionStopReq");
    }
    if (iso1Doc.V2G_Message.Body.SessionStopRes_isUsed) {
        addMessageName("SessionStopRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.SessionStopRes.ResponseCode);
    }

    if (iso1Doc.V2G_Message.Body.WeldingDetectionReq_isUsed) {
        addMessageName("WeldingDetectionReq");
        #define m iso1Doc.V2G_Message.Body.WeldingDetectionReq
        sprintf(sTmp, "%d", m.DC_EVStatus.EVReady); addProperty("DC_EVStatus.EVReady", sTmp);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVErrorCode); addProperty("DC_EVStatus.EVErrorCode", sTmp);
        translateiso1DC_EVErrorCodeTypeToJson(m.DC_EVStatus.EVErrorCode);
        sprintf(sTmp, "%d", m.DC_EVStatus.EVRESSSOC); addProperty("DC_EVStatus.EVRESSSOC", sTmp);    
        #undef m
    }
    if (iso1Doc.V2G_Message.Body.WeldingDetectionRes_isUsed) {
        addMessageName("WeldingDetectionRes");
        translateIso1ResponseCodeToJson(iso1Doc.V2G_Message.Body.WeldingDetectionRes.ResponseCode);
        #define m iso1Doc.V2G_Message.Body.WeldingDetectionRes        
        #define v1 m.DC_EVSEStatus.EVSEIsolationStatus
        #define v2 m.DC_EVSEStatus.EVSEIsolationStatus_isUsed
        #define v3 m.DC_EVSEStatus.EVSEStatusCode
        #define v4 m.DC_EVSEStatus.NotificationMaxDelay /* expected time until the PEV reacts on the below mentioned notification. Not relevant. */
        #define v5 m.DC_EVSEStatus.EVSENotification
        sprintf(sTmp, "%d", v1); addProperty("DC_EVSEStatus.EVSEIsolationStatus", sTmp);
        sprintf(sTmp, "%d", v2); addProperty("DC_EVSEStatus.EVSEIsolationStatus_isUsed", sTmp);
        sprintf(sTmp, "%d", v3); addProperty("DC_EVSEStatus.EVSEStatusCode", sTmp);
        translateiso1DC_EVSEStatusCodeTypeToJson(v3);
        sprintf(sTmp, "%d", v4); addProperty("DC_EVSEStatus.NotificationMaxDelay", sTmp);
        sprintf(sTmp, "%d", v5); addProperty("DC_EVSEStatus.EVSENotification", sTmp);
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Multiplier); addProperty("EVSEPresentVoltage.Multiplier", sTmp);
        sprintf(sTmp, "%d", m.EVSEPresentVoltage.Value); addProperty("EVSEPresentVoltage.Value", sTmp);
        translateIso1UnitToJson("EVSEPresentVoltage.Unit", m.EVSEPresentVoltage.Unit); 
        #undef v1
        #undef v2
        #undef v3
        #undef v4
        #undef v5
        #undef m
    }
}


/*********************************************************************************************************
*  Encoder
**********************************************************************************************************
*********************************************************************************************************/

void encodeIso1SessionSetupRequest(void) {
}

void encodeIso1SessionSetupResponse(void) {
}

void encodeIso1ServiceDiscoveryRequest(void) {
}

void encodeIso1ServiceDiscoveryResponse(void) {
}

void encodeIso1ServicePaymentSelectionRequest(void) { } /* DIN name is ServicePaymentSelection, but ISO name is PaymentServiceSelection */

void encodeIso1ServicePaymentSelectionResponse(void) { } /* DIN name is ServicePaymentSelection, but ISO name is PaymentServiceSelection */

void encodeIso1ChargeParameterDiscoveryRequest(void) {
}

void encodeIso1ChargeParameterDiscoveryResponse(void) {
}

void encodeIso1CableCheckRequest(void) {
}

void encodeIso1CableCheckResponse(void) {
}

void encodeIso1PreChargeRequest(void) {
}

void encodeIso1PreChargeResponse(void) {
}

void encodeIso1PowerDeliveryRequest(void) {
}

void encodeIso1PowerDeliveryResponse(void) {
}

void encodeIso1CurrentDemandRequest(void) {
}

void encodeIso1CurrentDemandResponse(void) {
}

void encodeIso1WeldingDetectionRequest(void) {
}

void encodeIso1WeldingDetectionResponse(void) {
}

void encodeIso1SessionStopRequest(void) {
}

void encodeIso1SessionStopResponse(void) {
}

void encodeIso1ContractAuthenticationRequest(void) {
}

void encodeIso1ContractAuthenticationResponse(void) {
}