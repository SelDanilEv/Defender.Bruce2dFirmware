# Graph Report - src  (2026-09-19)

## Corpus Check
- cluster-only mode — file stats not available

## Summary
- 5511 nodes · 13342 edges · 255 communities (238 shown, 7 thin omitted)
- Extraction: 79% EXTRACTED · 21% INFERRED · 0% AMBIGUOUS · INFERRED: 2771 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `c7eddff3`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- displayError
- BLE_Suite.h
- ducky_typer.cpp
- clients.cpp
- KarmaRuntimeState
- EspConnection
- loopOptions
- BLE_Suite.cpp
- M5SysWireAdapter
- BruceConfig
- deinitBLE
- nrf_mousejack.cpp
- RFScan
- rf_keeloq.cpp
- TagOMatic
- sniffer.cpp
- IrRead
- ST25R3916
- display_js.cpp
- clicker.cpp
- config.cpp
- karma_attack.cpp
- rf_send.cpp
- padprintln
- main_menu.h
- RFID2
- tftLogger.cpp
- NimBLEAddress
- Wardriving
- rf_decoder.cpp
- display.cpp
- EvilPortal
- RFIDInterface
- ActiveBroadcastAttack
- main.cpp
- PN532.cpp
- RepeaterState
- ObdDashboard
- PN532KillerTools.cpp
- wifi_atks.cpp
- ST25R3916.cpp
- MainMenu
- Pn532ble
- globals_js.cpp
- String
- PN532KillerTools
- GPSTracker
- LoRaRF.cpp
- EMVReader
- wifi_repeater.cpp
- BackgroundPortal
- mykeyboard.cpp
- getFsStorage
- ARPScanner.cpp
- AudioPlayerState
- brucegotchi_start
- ScrollableTextArea
- Elm327Client
- obd_pids.cpp
- structs.h
- rf_raw_record_create
- drawMainBorderWithTitle
- RFID125
- initRfModule
- rf_commands.cpp
- rfalNfcDevice
- displayTextLine
- Timer
- dialog_js.cpp
- HIDDeviceProfile
- drawMainBorder
- processQueuedProbeEvents
- set
- loopSD
- DHCPStarvation
- FastPairCrypto
- responder.cpp
- Gif
- cli.cpp
- themeInfo
- execute
- _emuMfcHandle
- ble_spam.cpp
- configPins.cpp
- RFJammer
- MifareKeysManager
- ir_jammer.cpp
- evil_portal.cpp
- sniffer_setup
- BruceConfigPins
- FS
- setup
- pwngrid.cpp
- ibutton.cpp
- rfid_js.cpp
- BLESerialService
- obd_dashboard.cpp
- U2fHidDevice
- u2f.cpp
- ApduCommand
- SSIDDatabase
- Amiibo
- wifiConnectMenu
- BleSpamConfig
- BleSpamListMetrics
- String
- led_control.cpp
- MassStorage
- webInterface.cpp
- ble_ninebot.cpp
- Wigle
- SPIPins
- ConfigMenu
- rfid_commands.cpp
- themeFiles
- MACFlooding
- gpio_js.cpp
- elm327_client.cpp
- audio.cpp
- utils.cpp
- ARPSpoofer
- EthernetHelper
- updateUi
- EvilPortalEndpoints
- vector
- BLE_API
- apdu.h
- wifi_recover.cpp
- ir_commands.cpp
- BleSpamRunState
- FastPairDeviceInfo
- executeHFPAttackChain
- WDGoWars
- TV-B-Gone.cpp
- PollScheduler
- shark_loop
- CredentialRecord
- .handleCbor
- rf_encoder.cpp
- String
- ModuleState
- USBSerial
- JS_IsTypedArray
- keyboard_js.cpp
- SnifferPacket
- fm.cpp
- rf_bruteforce.cpp
- SnifferQueueItem
- ble_common.cpp
- net_utils.cpp
- fillInfo
- js_get_path_from_params
- .handleRegister
- emulate
- enableNaptWhenAccessPointReady
- I2CPins
- StartupApp::StartupApp
- setup
- BleSpamEditState
- Opt_Coord
- powerSave.cpp
- readDecryptedFile
- musicPlayerUI
- badusb_js.cpp
- UILayout
- CborCursor
- _bytesToHex
- loadFile
- wifi_crack_handshake
- power_commands.cpp
- spam.cpp
- helpers.h
- StartupApp
- device_js.cpp
- subghz_js.cpp
- wifi_js.cpp
- BatteryService
- qrcode_menu.cpp
- rf_find_protocol
- PN532ServerCallbacks
- WordlistReader
- BleSpamAttackType
- EthernetMenu
- optionsMenu
- read
- CrackShared
- HandshakeData
- NRF24Menu
- OthersMenu
- BLESerialService.h
- buffer_js.cpp
- i2c_js.cpp
- menu_js.cpp
- bleSpamMenuUi
- MifareClassicDump
- EapolFrame
- UARTPins
- gpio_commands.cpp
- wifi_commands.cpp
- HmacSha1Pre
- nrf24_js.cpp
- serial_js.cpp
- BruceBLEService
- TaskBinding
- PlayerState
- `rf/protocols/` — RF Protocol Definitions (sub-GHz)
- channel_analyzer_setup
- jam_detect.cpp
- pcap_hdr_t
- CaptiveRequestHandler
- BleSpamTxPower
- RFMenu
- sound_commands.cpp
- wifiMACMenu
- led_js.cpp
- math_js.cpp
- runtime_js.cpp
- AutoCleanup
- ElmReply
- wifi_header_t
- socks4Proxy
- MyCallbacks
- setupSdCard
- wg_setup
- ble_js.cpp
- DisplayTarget
- APInfo
- PidSupport
- EMVAID
- audio_js.cpp
- BLESerialCallbacks
- ThrottleMethod
- BeaconFrame
- pcaprec_hdr_s
- pcaprec_hdr_t
- setEvilPasswordMode
- evil_portal.h
- Reading
- native_notifyBlink
- AppleProximityDevice
- BleSpamAppleDevice
- PwEntry
- String
- Option
- vector

## God Nodes (most connected - your core abstractions)
1. `loopOptions()` - 205 edges
2. `displayError()` - 176 edges
3. `ST25R3916` - 128 edges
4. `padprintln()` - 125 edges
5. `BruceConfig` - 112 edges
6. `KarmaRuntimeState` - 86 edges
7. `getFsStorage()` - 85 edges
8. `drawMainBorderWithTitle()` - 84 edges
9. `U2fHidDevice` - 83 edges
10. `EvilPortal` - 80 edges

## Surprising Connections (you probably didn't know these)
- `addEvilWifiMenu()` --calls--> `keyboard()`  [INFERRED]
  src/core/settings.cpp → src/core/mykeyboard.cpp
- `addMifareKeyMenu()` --calls--> `keyboard()`  [INFERRED]
  src/core/settings.cpp → src/core/mykeyboard.cpp
- `setEvilEndpointCreds()` --calls--> `keyboard()`  [INFERRED]
  src/core/settings.cpp → src/core/mykeyboard.cpp
- `setEvilEndpointSsid()` --calls--> `keyboard()`  [INFERRED]
  src/core/settings.cpp → src/core/mykeyboard.cpp
- `nrf_info()` --calls--> `padprintln()`  [INFERRED]
  src/modules/NRF24/nrf_common.cpp → src/core/display.cpp

## Import Cycles
- None detected.

## Communities (255 total, 7 thin omitted)

### Community 0 - "displayError"
Cohesion: 0.05
Nodes (92): arduino_event_id_t, arduino_event_info_t, ChameleonUltra, displayError(), displaySuccess(), keyboard(), checkLittleFsSize(), HfTag (+84 more)

### Community 1 - "BLE_Suite.h"
Cohesion: 0.03
Nodes (87): BLEStateManager, activeClients, bleInitialized, cleanupAllClients, currentDeviceName, getCurrentDeviceName, BruceConfig, CharacteristicInfo (+79 more)

### Community 2 - "ducky_typer.cpp"
Cohesion: 0.06
Nodes (77): displayWarning(), optionsMenu, badusbBufferCallback(), badusbFileCallback(), cmd, DuckyCommandType, err_t, HIDInterface (+69 more)

### Community 3 - "clients.cpp"
Cohesion: 0.08
Nodes (74): ClientProtocol, Fn, IPAddress, ESPNetifEthernetClient, client_close, connect, connected, close (+66 more)

### Community 4 - "KarmaRuntimeState"
Cohesion: 0.03
Nodes (74): ActiveNetwork, AttackConfig, KarmaConfig, KarmaMode, map, QueueHandle_t, TaskHandle_t, KarmaRuntimeState (+66 more)

### Community 5 - "EspConnection"
Cohesion: 0.06
Nodes (61): File, String, EspConnection, appendPeerToList, beginEspnow, beginSend, broadcastAddress, createFileMessage (+53 more)

### Community 6 - "loopOptions"
Cohesion: 0.06
Nodes (66): loopOptions(), setLedBrightnessConfig(), setLedEffectDirectionConfig(), setLedEffectSpeedConfig(), hideAppsMenu, displayUIMenu, pinsMenu, optionsMenu (+58 more)

### Community 7 - "BLE_Suite.cpp"
Cohesion: 0.06
Nodes (59): TouchFooter(), AudioAttackService, attackAudioMedia, attackAVRCP, attackTelephony, crashAudioStack, executeAudioAttack, findAndAttackAudioServices (+51 more)

### Community 8 - "M5SysWireAdapter"
Cohesion: 0.05
Nodes (46): acquireI2CBus(), acquireSharedSPI(), acquireSPIBus(), checkAndRecoverSysI2CBus(), function, gpio_num_t, SemaphoreHandle_t, SPIClass (+38 more)

### Community 9 - "BruceConfig"
Cohesion: 0.04
Nodes (62): BruceConfig, automaticTimeUpdateViaNTP, badUSBBLEKeyboardLayout, badUSBBLEKeyDelay, badUSBBLEShowOutput, bright, clock24hr, colorInverted (+54 more)

### Community 10 - "deinitBLE"
Cohesion: 0.14
Nodes (61): attemptConnectionWithStrategies(), exploitAuthBypass, forceRepairing, disable, deinitBLE, initBLE, registerClient, unregisterClient (+53 more)

### Community 11 - "nrf_mousejack.cpp"
Cohesion: 0.07
Nodes (47): BLEJamMode, MjDeviceType, MjHidKey, MjTarget, nrf_info(), nrf_setMode(), nrf_start(), NimBLEAddress (+39 more)

### Community 12 - "RFScan"
Cohesion: 0.06
Nodes (59): decimalToHexString(), String, rf_build_raw(), RfCodes, String, vector, display_info(), display_signal_data() (+51 more)

### Community 13 - "rf_keeloq.cpp"
Cohesion: 0.06
Nodes (57): FS, String, vector, vector, keeloq_build_hop(), keeloq_decrypt(), keeloq_derive_man(), keeloq_embedded_plaintext() (+49 more)

### Community 14 - "TagOMatic"
Cohesion: 0.08
Nodes (55): RFID_State, String, displaySmallErrorToast(), RFID_State, set, String, vector, TagOMatic (+47 more)

### Community 15 - "sniffer.cpp"
Cohesion: 0.08
Nodes (51): esp_event_base_t, analyzeFrame(), buildHandshakePath(), cacheBeaconFrame(), classifyEapolMessage(), cleanupStaleBeacons(), copyMac(), copySsidToBuffer() (+43 more)

### Community 16 - "IrRead"
Cohesion: 0.08
Nodes (51): IRrecv, JSContext, JSValue, native_irRead(), native_irReadRaw(), native_irTransmit(), native_irTransmitFile(), decode_results (+43 more)

### Community 17 - "ST25R3916"
Cohesion: 0.04
Nodes (52): CONNECTION_TYPE, Crypto1State, SPIClass, String, ST25R3916, _connection_type, _discoveryStarted, _emuCipher (+44 more)

### Community 18 - "display_js.cpp"
Cohesion: 0.15
Nodes (49): JSContext, JSValue, get_display(), get_display_target(), native_color(), native_createSprite(), native_deleteSprite(), native_drawArc() (+41 more)

### Community 19 - "clicker.cpp"
Cohesion: 0.07
Nodes (42): ClickerConfig, wakeUpScreen(), LayoutConfig, MenuItem, JSContext, JSValue, native_micCaptureSamples(), native_micRecordWav() (+34 more)

### Community 20 - "config.cpp"
Cohesion: 0.06
Nodes (36): addDisabledMenu, addEvilWifiName, addMifareKey, addQrCodeEntry, addWebUISession, addWifiCredential, ensureMifareKeysLoaded, ensureRepeaterApCredentials (+28 more)

### Community 21 - "karma_attack.cpp"
Cohesion: 0.09
Nodes (45): setupLittleFS(), launchAttackForResponse, sendBeaconFrame, activePortalCount(), buildBeaconFrame(), buildEnhancedProbeResponse(), checkCloneAttackOpportunities(), checkForAssociations() (+37 more)

### Community 22 - "rf_send.cpp"
Cohesion: 0.07
Nodes (37): String, dec2binWzerofill(), hexCharToDecimal(), hexStringToDecimal(), hexStringToU64(), hexStrToBinStr(), FS, RfCodes (+29 more)

### Community 23 - "padprintln"
Cohesion: 0.09
Nodes (44): receiveFile, sendFile, getColorVariation(), padprint(), padprintln(), progressHandler(), display_banner, FS (+36 more)

### Community 24 - "main_menu.h"
Cohesion: 0.06
Nodes (18): MenuItemInterface, BleMenu, configMenu, drawIcon, setBleNameMenu, MenuItemInterface, ConnectMenu, drawIcon (+10 more)

### Community 25 - "RFID2"
Cohesion: 0.08
Nodes (40): MFRC522, MFRC522DriverPinSimple, BruceMFRC522DriverI2C, _slaveAdr, byte, MFRC522Driver, String, TwoWire (+32 more)

### Community 26 - "tftLogger.cpp"
Cohesion: 0.05
Nodes (14): String, tft_logger::drawCentreString(), tft_logger::drawRightString(), tft_logger::drawString(), tft_logger::imageToBin(), tft_logger::isLogEqual(), tft_logger::log_drawString(), tft_logger::log_print() (+6 more)

### Community 27 - "NimBLEAddress"
Cohesion: 0.10
Nodes (45): FastPairExploitType, FastPairPopupType, FastPairVersion, NimBLEAddress, NimBLERemoteCharacteristic, detectFastPairVersion(), FastPairExploitEngine, createFastPairAdvertisement (+37 more)

### Community 28 - "Wardriving"
Cohesion: 0.07
Nodes (43): String, wifi_auth_mode_t, HardwareSerial, set, String, TinyGPSPlus, parseMacToU64(), Wardriving (+35 more)

### Community 29 - "rf_decoder.cpp"
Cohesion: 0.08
Nodes (36): RfCodes, RfProtocolDef, rmt_channel_handle_t, rmt_rx_done_event_data_t, rmt_symbol_word_t, vector, QueueHandle_t, rmt_channel_handle_t (+28 more)

### Community 30 - "display.cpp"
Cohesion: 0.10
Nodes (34): buildPngBinPath(), File, FS, String, displayMessage(), displayScrollingText(), drawBatteryStatus(), drawBLESmall() (+26 more)

### Community 31 - "EvilPortal"
Cohesion: 0.05
Nodes (37): AsyncWebServer, EvilPortal, apGateway, apName, _autoMode, _autoTemplateFile, _backgroundMode, _baseDurationSec (+29 more)

### Community 32 - "RFIDInterface"
Cohesion: 0.06
Nodes (31): Adafruit_PN532, String, NdefMessage, PrintableUID, String, vector, RFIDInterface, begin (+23 more)

### Community 33 - "ActiveBroadcastAttack"
Cohesion: 0.06
Nodes (40): ActiveBroadcastAttack, _active, batchStart, broadcastSSID, clearHighPrioritySSIDs, config, currentBatch, currentChannel (+32 more)

### Community 34 - "main.cpp"
Cohesion: 0.08
Nodes (21): begin, CmdPacket, text, handleSerialCommands(), _serialCmdsTaskLoop(), startSerialCommandsHandlerTask(), removeEvilWifiMenu(), backToMenu() (+13 more)

### Community 35 - "PN532.cpp"
Cohesion: 0.11
Nodes (37): hexToStr(), byte, CONNECTION_TYPE, String, CONNECTION_TYPE, PN532, authenticate_mifare_classic, begin (+29 more)

### Community 36 - "RepeaterState"
Cohesion: 0.10
Nodes (35): CleanupPlan, actions, count, CleanupAction, RepeaterFailure, RepeaterPhase, failureText(), CleanupAction (+27 more)

### Community 37 - "ObdDashboard"
Cohesion: 0.07
Nodes (35): ConsumptionSource, addTask(), buildTasks(), draw(), obd_dashboard_setup(), ObdDashboard, activeThrottleIdx, battery (+27 more)

### Community 38 - "PN532KillerTools.cpp"
Cohesion: 0.16
Nodes (35): displayInfo(), drawCreditCard(), drawMfkey32Icon(), drawMfkey64Icon(), printCenterFootnote(), printSubtitle(), disableBleDataTransfer, disableTcpDataTransfer (+27 more)

### Community 39 - "wifi_atks.cpp"
Cohesion: 0.13
Nodes (34): cleanlyStopWebUiForWiFiFeature(), esp_err_t, wifiRawTx(), HandshakeTracker, msg1, msg2, msg3, msg4 (+26 more)

### Community 40 - "ST25R3916.cpp"
Cohesion: 0.11
Nodes (35): CONNECTION_TYPE, NdefMessage, vector, _setNfcPower(), st25BuildNdefMessageFromStruct(), st25ExtractNdefMessageFromPageDump(), st25HexNibble(), st25ParseHexBytesAfterColon() (+27 more)

### Community 41 - "MainMenu"
Cohesion: 0.07
Nodes (27): vector, MainMenu, bleMenu, clockMenu, configMenu, connectMenu, _currentIndex, fileMenu (+19 more)

### Community 42 - "Pn532ble"
Cohesion: 0.07
Nodes (32): checkLetterShortcutPress(), String, vector, AppMode, String, vector, Pn532ble, buffer (+24 more)

### Community 43 - "globals_js.cpp"
Cohesion: 0.17
Nodes (33): JSTimerContextState, JSContext, JSValue, get_timer_state(), js_add_main_timer(), js_clearInterval(), js_clearTimeout(), js_date_now() (+25 more)

### Community 44 - "String"
Cohesion: 0.12
Nodes (34): AuthBypassEngine, addKnownDevice, attemptSpoofConnection, AuthBypassEngine::AuthBypassEngine(), getSpoofAddress, knownDevices, String, getScriptFromUser() (+26 more)

### Community 45 - "PN532KillerTools"
Cohesion: 0.06
Nodes (33): IPAddress, String, WiFiClient, PN532KillerTools, connect, _deviceInitialized, displayBanner, _initializationFailed (+25 more)

### Community 46 - "GPSTracker"
Cohesion: 0.09
Nodes (31): padprintf(), File, GPSTracker, add_coord, add_final_file_data, add_initial_file_data, begin_gps, create_filename (+23 more)

### Community 47 - "LoRaRF.cpp"
Cohesion: 0.10
Nodes (27): MenuItemInterface, LoRaMenu, configMenu, drawIcon, optionsMenu, changeusername(), chfreq(), clearLoraRadio() (+19 more)

### Community 48 - "EMVReader"
Cohesion: 0.15
Nodes (30): BinToAscii(), string, vector, EMVCard, aid, pan, pan_len, parsed (+22 more)

### Community 49 - "wifi_repeater.cpp"
Cohesion: 0.15
Nodes (31): ApMenuResult, ConnectAttemptResult, isWifiTransitioning(), applyAccessPointCredentials(), attemptUpstreamConnect(), cancelAndCleanup(), chooseUpstream(), clearRepeaterState() (+23 more)

### Community 50 - "BackgroundPortal"
Cohesion: 0.07
Nodes (31): map, getStats, BackgroundPortal, capturedPassword, channel, clientFingerprint, hasCreds, instance (+23 more)

### Community 51 - "mykeyboard.cpp"
Cohesion: 0.09
Nodes (28): box_t, color, h, key, key_sh, touch_id, w, x (+20 more)

### Community 52 - "getFsStorage"
Cohesion: 0.15
Nodes (31): getFsStorage(), copyCallback(), cmd, SimpleCLI, String, crc16(), crc16_update(), crc32Callback() (+23 more)

### Community 53 - "ARPScanner.cpp"
Cohesion: 0.08
Nodes (27): esp_ping_handle_t, ip_addr_t, ARPScanner, afterScanOptions, arpRequestDelay, esp_net_interface, gateway, hostslist_eth (+19 more)

### Community 54 - "AudioPlayerState"
Cohesion: 0.08
Nodes (27): AudioFileSource, AudioGenerator, AudioOutputI2S, AudioPlaybackInfo, audioPlaybackTask(), AudioPlayerState, currentFile, currentGain (+19 more)

### Community 55 - "brucegotchi_start"
Cohesion: 0.10
Nodes (29): BrucePhase, setMood(), advertise(), advertisePhase(), brucegotchi_setup(), brucegotchi_start(), bruceMacToKey(), BruceState (+21 more)

### Community 56 - "ScrollableTextArea"
Cohesion: 0.09
Nodes (30): printTitle(), File, String, String, vector, ScrollableTextArea, clear, firstVisibleLine (+22 more)

### Community 57 - "Elm327Client"
Cohesion: 0.07
Nodes (27): Elm327Client, abortCheck, abortRequested, adapterResponding, awaitingPrompt, client, CONNECT_TIMEOUT_MS, consecutiveFailures (+19 more)

### Community 58 - "obd_pids.cpp"
Cohesion: 0.12
Nodes (24): classifyReply(), classifyTerminal(), ConsumptionSample, fuelRateLh, rateOk, speedKmh, speedOk, ReplyStatus (+16 more)

### Community 59 - "structs.h"
Cohesion: 0.08
Nodes (16): rf_raw_emit_draw(), rf_listen(), rf_listen_beep(), RfCodes, FreqFound, freq, rssi, HighLow (+8 more)

### Community 60 - "rf_raw_record_create"
Cohesion: 0.09
Nodes (30): rmt_channel_t, rmt_rx_done_event_data_t, rmt_symbol_word_t, vector, record_rmt_rx_done_callback(), rf_durations_to_rmt_symbols(), rf_freq_scan(), rf_raw_record() (+22 more)

### Community 61 - "drawMainBorderWithTitle"
Cohesion: 0.22
Nodes (29): drawMainBorderWithTitle(), buildOptimizedDeauthFrame(), buildTargetListFromScan(), cacheSameSSIDAPs(), Host, vector, deauthAllByChannel(), deauthAllFromScan() (+21 more)

### Community 62 - "RFID125"
Cohesion: 0.11
Nodes (28): RFID125_State, String, HardwareSerial, RFID125_State, String, hex2digit(), hex2int(), RFID125 (+20 more)

### Community 63 - "initRfModule"
Cohesion: 0.13
Nodes (25): rfTxCallback(), _setup_gpio(), rf_raw_emit(), rf_scan(), rfTransmitCode(), rf_CC1101_rssi(), cc1101ApplyFixedFreqOokPreset(), cc1101ApplyPreciseCalibration() (+17 more)

### Community 64 - "rf_commands.cpp"
Cohesion: 0.16
Nodes (27): cmd, Command, SimpleCLI, createRfCommands(), createRfKeeloqFileTestCommand(), createRfKeeloqTestCommand(), createRfKeeloqTxCommand(), createRfMfcodesCommand() (+19 more)

### Community 65 - "rfalNfcDevice"
Cohesion: 0.15
Nodes (28): _deselectSharedSpiDevices(), _buildEmuMfc, clone, erase, _eraseUltralight, _isUltralightUserPage, _mfcHalt, _mfcRebuildStrAllPages (+20 more)

### Community 66 - "displayTextLine"
Cohesion: 0.21
Nodes (24): displayTextLine(), addToRecentCodes(), chooseCmdIrFile(), FS, IRCode, String, otherIRcodes(), resetCodesArray() (+16 more)

### Community 67 - "Timer"
Cohesion: 0.13
Nodes (22): ClockMenu, drawIcon, optionsMenu, showSubMenu, MenuItemInterface, Timer, clearUnderline, drawSoundOption (+14 more)

### Community 68 - "dialog_js.cpp"
Cohesion: 0.23
Nodes (26): fromString, JSContext, JSValue, getAreaPointer(), native_dialogChoice(), native_dialogCreateTextViewer(), native_dialogCreateTextViewerClear(), native_dialogCreateTextViewerClose() (+18 more)

### Community 70 - "HIDDeviceProfile"
Cohesion: 0.08
Nodes (27): vector, HIDDeviceProfile, connectionBehavior, deviceName, hasExistingBond, isAndroidDevice, isAppleDevice, isIoTDevice (+19 more)

### Community 71 - "drawMainBorder"
Cohesion: 0.26
Nodes (24): drawMainBorder(), addLine, draw, scrollDown, AppMode, getMifareClassicSectorCount, hf14aMfReadDumpMode, hf14aMfuReadDumpMode (+16 more)

### Community 72 - "processQueuedProbeEvents"
Cohesion: 0.13
Nodes (25): AttackTier, ClientBehavior, getTopResponses, analyzeClientBehavior(), calculateAttackPriority(), vector, determineAttackTier(), enqueuePendingPortal() (+17 more)

### Community 73 - "set"
Cohesion: 0.12
Nodes (19): setUiColor, set, BruceTheme, bgColor, openThemeFile, priColor, removeTheme, secColor (+11 more)

### Community 74 - "loopSD"
Cohesion: 0.25
Nodes (24): displayRedStripe(), checkExt(), copyFile(), copyToFs(), File, FileList, FS, String (+16 more)

### Community 75 - "DHCPStarvation"
Cohesion: 0.12
Nodes (22): dhcp_msg, DHCPStarvation, broadcast_mac_address, change_mac_in_packet, dhcp_payload, ethernet_frame, ipv4_pkt, loop (+14 more)

### Community 76 - "FastPairCrypto"
Cohesion: 0.12
Nodes (23): mbedtls_aes_context, mbedtls_ctr_drbg_context, mbedtls_ecp_group, mbedtls_mpi, FastPairCrypto, aes_ctx, ctr_drbg, d (+15 more)

### Community 77 - "responder.cpp"
Cohesion: 0.13
Nodes (21): buildNTLMType2Msg(), IPAddress, String, WiFiClient, decodeNetBIOSLabel(), extractAndPrintHash(), getIPAddress(), getWindowsTimestamp() (+13 more)

### Community 78 - "Gif"
Cohesion: 0.09
Nodes (18): AnimatedGIF, Gif, closeFile, getLastError, gif, GIFDraw, GifFs, gifPosition (+10 more)

### Community 79 - "cli.cpp"
Cohesion: 0.14
Nodes (6): cmd_error, cliErrorCallback(), SimpleCLI, String, SerialCli, _cli

### Community 80 - "themeInfo"
Cohesion: 0.08
Nodes (24): themeInfo, ble, boot_img, boot_sound, border, clock, config, connect (+16 more)

### Community 81 - "execute"
Cohesion: 0.21
Nodes (24): BLEAttackManager, cleanupAfterAttack, connectToDevice, prepareForConnection, profileDevice, testBufferOverflow, testCharacteristicAccess, testServiceDiscovery (+16 more)

### Community 82 - "_emuMfcHandle"
Cohesion: 0.22
Nodes (21): Crypto1State, crypto1_bit(), crypto1_byte(), crypto1_filter(), crypto1_filter_bit(), crypto1_init(), crypto1_parity(), crypto1_swapendian() (+13 more)

### Community 83 - "ble_spam.cpp"
Cohesion: 0.16
Nodes (22): BLEAdvertisementData, EBLEPayloadType, bleSpamBuildAdvertisementData(), bleSpamBuildAppleContinuityAdvertisement(), bleSpamBuildContinuityNearbyAction(), bleSpamFastRandomMac(), bleSpamIsCacheable(), bleSpamNextRand64() (+14 more)

### Community 84 - "configPins.cpp"
Cohesion: 0.13
Nodes (22): factoryReset, setGpsBaudrate, setiButtonPin, setIrRxPin, setIrTxPin, setIrTxRepeats, setRfFreq, setRfFxdFreq (+14 more)

### Community 85 - "RFJammer"
Cohesion: 0.19
Nodes (21): getComplementaryColor2(), RFJamMode, RFJamMode, RFJammer, display_banner, isCC1101, jamMode, nTransmitterPin (+13 more)

### Community 86 - "MifareKeysManager"
Cohesion: 0.30
Nodes (21): FS, set, String, MifareKeysManager, addKey, appendToFile, appendToFS, clear (+13 more)

### Community 87 - "ir_jammer.cpp"
Cohesion: 0.27
Nodes (22): JammerState, adjustModeSpecificSetting(), cleanupJammer(), IRsend, displayStats(), getFrequency(), getModeName(), handleJammerInput() (+14 more)

### Community 88 - "evil_portal.cpp"
Cohesion: 0.15
Nodes (22): apName_from_keyboard, beginAP, checkAndExtendDuration, drawScreen, EvilPortal::EvilPortal(), hasCredentials, hasRecentActivity, hasRecentPageView (+14 more)

### Community 89 - "sniffer_setup"
Cohesion: 0.20
Nodes (23): closeDeauthFile(), closeRawFile(), File, FS, TickType_t, deauthCaptureEnabled(), ensureDirectories(), handleDeauthWrite() (+15 more)

### Community 90 - "BruceConfigPins"
Cohesion: 0.09
Nodes (21): BruceConfigPins, bleName, filepath, gps_bus, gpsBaudrate, i2c_bus, iButton, irRx (+13 more)

### Community 91 - "FS"
Cohesion: 0.12
Nodes (14): FS, ARPoisoner, arpPCAPfile, gatewayIP, gatewayMAC, loop, pcapFile, sendARPPacket (+6 more)

### Community 92 - "setup"
Cohesion: 0.11
Nodes (20): SimpleCLI, createBadUsbCommands(), SerialCli::SerialCli(), setup, SimpleCLI, createCryptoCommands(), SimpleCLI, createRfidCommands() (+12 more)

### Community 93 - "pwngrid.cpp"
Cohesion: 0.10
Nodes (19): ensureWifiPlatform(), add_new_peer(), checkPwngridGoneFriends(), JsonDocument, String, vector, wifi_promiscuous_pkt_type_t, delete_peer_gone() (+11 more)

### Community 94 - "ibutton.cpp"
Cohesion: 0.18
Nodes (20): IButtonResult, MenuAction, bufferCrcValid(), bufferToHexStr(), byte, String, displayStatus(), doLoad() (+12 more)

### Community 95 - "rfid_js.cpp"
Cohesion: 0.25
Nodes (19): clearSRIXReader(), clearTagReader(), JSContext, JSValue, getSRIXReader(), getTagReader(), native_rfid_AddMifareKey(), native_rfidClear() (+11 more)

### Community 96 - "BLESerialService"
Cohesion: 0.16
Nodes (19): BLESerialService, available, callbacks, end, print, println, read, readStringUntil (+11 more)

### Community 97 - "obd_dashboard.cpp"
Cohesion: 0.22
Nodes (19): String, logInfo(), percentText(), pollBattery(), pollConsumption(), pollFuelLevel(), pollFuelRateLh(), pollLoadAlt() (+11 more)

### Community 98 - "U2fHidDevice"
Cohesion: 0.10
Nodes (14): mbedtls_ecp_point, U2fHidDevice, _attestationCertDer, _counter, _hid, _masterLoaded, _masterSecret, _nextCid (+6 more)

### Community 99 - "u2f.cpp"
Cohesion: 0.10
Nodes (18): drawU2fStatusScreen(), PendingCommandState, cid, cmd, len, ready, RxMessageState, active (+10 more)

### Community 100 - "ApduCommand"
Cohesion: 0.09
Nodes (22): ApduCommand, C_APDU_CLA, C_APDU_DATA, C_APDU_INS, C_APDU_LC, C_APDU_P1, C_APDU_P1_SELECT_BY_ID, C_APDU_P1_SELECT_BY_NAME (+14 more)

### Community 101 - "SSIDDatabase"
Cohesion: 0.18
Nodes (22): restart, start, File, SSIDDatabase, clearCache, currentFilename, findSSID, getAverageLength (+14 more)

### Community 102 - "Amiibo"
Cohesion: 0.16
Nodes (18): Amiibolink, Amiibo, amiibolink, changeUIDMode, checkEmulationTagType, currentMode, delayWithReturn, displayBanner (+10 more)

### Community 103 - "wifiConnectMenu"
Cohesion: 0.21
Nodes (19): radioHasMemForBle(), radioHasMemForWifi(), radioLargestDmaBlock(), wifiCallback(), checkMAC(), _connectToWifiNetwork(), String, wifi_mode_t (+11 more)

### Community 104 - "BleSpamConfig"
Cohesion: 0.15
Nodes (21): bleSpamAdjustMs(), BleSpamConfig, adv_ms, gap_ms, mac_rand_mode, tx_power, bleSpamConfigScreen(), bleSpamDeinitAdvertiser() (+13 more)

### Community 105 - "BleSpamListMetrics"
Cohesion: 0.13
Nodes (21): bleSpamEnsureScroll(), bleSpamGetListMetrics(), bleSpamListLoop(), BleSpamListMetrics, footer_y, list_h, list_w, list_x (+13 more)

### Community 106 - "String"
Cohesion: 0.16
Nodes (21): addHighPrioritySSID, processProbeResponse, recordResponse, addMACToCache(), classifyEAPOLMessage(), copyStringToBuffer(), String, wifi_promiscuous_pkt_t (+13 more)

### Community 107 - "led_control.cpp"
Cohesion: 0.23
Nodes (19): alterOneColorChannel(), beginLed(), blinkLed(), function, hsvToRgb(), ledEffects(), ledPreviewMode(), ledSetup() (+11 more)

### Community 108 - "MassStorage"
Cohesion: 0.19
Nodes (14): drawUSBStickIcon(), MassStorage, beginUsb, displayMessage, loop, msc, setup, setupUsbCallback (+6 more)

### Community 109 - "webInterface.cpp"
Cohesion: 0.23
Nodes (19): String, parseSerialCommand(), checkUserWebAuth(), color565ToWebHex(), configureWebServer(), AsyncWebServerRequest, FS, String (+11 more)

### Community 110 - "ble_ninebot.cpp"
Cohesion: 0.15
Nodes (17): BLENinebot, BLENinebot::BLENinebot(), clientDisconnect, loop, redrawMainBorder, setup, buildModelOptions(), NimBLEClient (+9 more)

### Community 111 - "Wigle"
Cohesion: 0.19
Nodes (17): File, FS, String, WiFiClientSecure, String, Wigle, auth_header, _check_token (+9 more)

### Community 112 - "SPIPins"
Cohesion: 0.16
Nodes (17): setCC1101Pins, BruceConfigPins::setLoRaPins(), setNrf24Pins, setPn532Pins, setSDCardPins, setSpiPins, BruceConfigPins::setSR25RPins(), BruceConfigPins::setW5500Pins() (+9 more)

### Community 113 - "ConfigMenu"
Cohesion: 0.20
Nodes (15): ConfigMenu, advancedMenu, audioMenu, devMenu, drawIcon, ledMenu, optionsMenu, powerMenu (+7 more)

### Community 114 - "rfid_commands.cpp"
Cohesion: 0.28
Nodes (18): _argTimeout(), cmd, Command, _createRfidModule(), _ensureRfid(), _printTagInfo(), _readTagWithTimeout(), rfidAutotestCallback() (+10 more)

### Community 115 - "themeFiles"
Cohesion: 0.11
Nodes (19): themeFiles, ble, boot_img, boot_sound, clock, config, connect, ethernet (+11 more)

### Community 116 - "MACFlooding"
Cohesion: 0.17
Nodes (16): eth_hdr, ip_hdr, MACFlooding, calculate_ip_checksum, change_mac_in_packet, eth_header, ethernet_frame, ipv4_pkt (+8 more)

### Community 117 - "gpio_js.cpp"
Cohesion: 0.28
Nodes (18): JSContext, JSValue, native_analogRead(), native_analogWrite(), native_analogWriteFrequency(), native_analogWriteResolution(), native_dacWrite(), native_digitalRead() (+10 more)

### Community 118 - "elm327_client.cpp"
Cohesion: 0.29
Nodes (18): appendCapped(), ReplyStatus, String, drainStale, ensureLink, finishFrame, initAdapter, open (+10 more)

### Community 119 - "audio.cpp"
Cohesion: 0.27
Nodes (18): FS, String, createConfiguredAudioOutput(), initAudioPlayer(), isAudioFile(), isAudioPlaying(), pauseAudioPlayback(), playAudioFile() (+10 more)

### Community 120 - "utils.cpp"
Cohesion: 0.14
Nodes (14): runClockLoop(), String, TwoWire, formatBytes(), formatTimeDecimal(), getOptionsJSON(), i2c_bulk_write(), printMemoryUsage() (+6 more)

### Community 121 - "ARPSpoofer"
Cohesion: 0.15
Nodes (16): ARPSpoofer, arpPCAPfile, gatewayIP, gatewayMAC, loop, mitm, myMAC, pcapFile (+8 more)

### Community 122 - "EthernetHelper"
Cohesion: 0.16
Nodes (14): SPIClass, EthernetHelper, ethEventId, ethNetif, ethSpi, generate_mac, is_connected, mac (+6 more)

### Community 123 - "updateUi"
Cohesion: 0.19
Nodes (12): String, getCurrentMoodFace(), getCurrentMoodId(), getCurrentMoodPhrase(), isCurrentMoodBroken(), String, drawFooterData(), drawMood() (+4 more)

### Community 124 - "EvilPortalEndpoints"
Cohesion: 0.12
Nodes (16): Credential, pwd, user, EvilPortalEndpoints, allowGetCreds, allowSetSsid, getCredsEndpoint, setSsidEndpoint (+8 more)

### Community 125 - "vector"
Cohesion: 0.13
Nodes (11): vector, String, wifi_mode_t, WiFiState, ap_active, ap_ssid, bssid, channel (+3 more)

### Community 126 - "BLE_API"
Cohesion: 0.15
Nodes (12): BLE_API, battery_service, end, pServer, serial_service, setup, update_mtu, BLEAPICallback (+4 more)

### Community 127 - "apdu.h"
Cohesion: 0.20
Nodes (15): appendWscAttr(), string, vector, vector, Ndef, mimeRecord, newMessage, RTD_URI (+7 more)

### Community 128 - "wifi_recover.cpp"
Cohesion: 0.28
Nodes (15): crack_worker_task(), derive_ptk(), hmac_sha1_precompute(), hmac_sha1_with_pre(), pbkdf2_precomp(), sha1_extract(), sha1_final(), sha1_init() (+7 more)

### Community 129 - "ir_commands.cpp"
Cohesion: 0.24
Nodes (15): cmd, Command, SimpleCLI, createIrCommands(), createIrRxCommand(), createIrTxBufferCommand(), createIrTxCommand(), createIrTxFileCommand() (+7 more)

### Community 130 - "BleSpamRunState"
Cohesion: 0.12
Nodes (16): BleSpamRunState, adv_active, adv_stop_ms, applied_power, cached_advertisement, cached_device_index, cached_type, cached_valid (+8 more)

### Community 131 - "FastPairDeviceInfo"
Cohesion: 0.12
Nodes (16): FastPairDeviceInfo, address, connected, deviceType, modelId, name, rssi, supportsFastPair (+8 more)

### Community 132 - "executeHFPAttackChain"
Cohesion: 0.30
Nodes (14): showHFPSubMenu(), NimBLEAddress, NimBLEClient, String, vector, HFPExploitEngine, attemptHFPHandshake, attemptHFPPivot (+6 more)

### Community 133 - "WDGoWars"
Cohesion: 0.25
Nodes (13): File, FS, String, WiFiClientSecure, WDGoWars, _check_api_key, _display_banner, host (+5 more)

### Community 134 - "TV-B-Gone.cpp"
Cohesion: 0.26
Nodes (13): IrCode, IRsend, delay_ten_us(), init_ir_tx_mutex(), lock_ir_tx(), quickflashLED(), quickflashLEDx(), read_bits() (+5 more)

### Community 135 - "PollScheduler"
Cohesion: 0.16
Nodes (11): advanceDue(), PollScheduler, addTask, dueTimes, intervals, markRan, MAX_TASKS, NONE_DUE (+3 more)

### Community 136 - "shark_loop"
Cohesion: 0.23
Nodes (14): checkCollisions(), detectInputs(), displayScore(), drawFish(), drawShark(), Fish, size, x (+6 more)

### Community 137 - "CredentialRecord"
Cohesion: 0.26
Nodes (8): FS, String, CredentialRecord, credId, credIdLen, path, rpIdHash, signCount

### Community 139 - "rf_encoder.cpp"
Cohesion: 0.23
Nodes (15): gpio_num_t, RfProtocolDef, rmt_symbol_word_t, String, vector, rf_encode_protocol(), rf_encoder_selftest(), rf_keeloq_durations() (+7 more)

### Community 140 - "String"
Cohesion: 0.21
Nodes (16): AsyncWebServerRequest, String, EvilPortal::CaptiveRequestHandler::handleRequest(), creds_GET, credsController, getCapturedPassword, getCapturedSSID, getHtmlTemplate (+8 more)

### Community 141 - "ModuleState"
Cohesion: 0.22
Nodes (13): active(), File, String, escape(), flush(), ModuleState, bytesWritten, file (+5 more)

### Community 142 - "USBSerial"
Cohesion: 0.16
Nodes (5): String, va_list, USBSerial, out, Stream

### Community 143 - "JS_IsTypedArray"
Cohesion: 0.26
Nodes (14): JsonVariantConst, native_drawJpg(), buffer_latin1_string_to_bytes(), buffer_latin1_to_string(), JSContext, JSValue, internal_print(), js_fatal_error_handler() (+6 more)

### Community 144 - "keyboard_js.cpp"
Cohesion: 0.35
Nodes (14): KeyboardType, JSContext, JSValue, keyboard_wrapper(), native_getAnyPress(), native_getEscPress(), native_getKeysPressed(), native_getNextPress() (+6 more)

### Community 145 - "SnifferPacket"
Cohesion: 0.19
Nodes (14): BLE_Sniffer(), BLE_SnifferMenu(), String, vector, parseManufacturerData(), payloadToHex(), SnifferPacket, address (+6 more)

### Community 146 - "fm.cpp"
Cohesion: 0.30
Nodes (13): fm_banner(), fm_begin(), fm_live_run(), fm_options(), fm_options_digit(), fm_options_frq(), fm_scan(), fm_setup() (+5 more)

### Community 147 - "rf_bruteforce.cpp"
Cohesion: 0.18
Nodes (13): BruteProtocol, bits, name, one, pilot, stop, zero, rf_brute_frequency() (+5 more)

### Community 148 - "SnifferQueueItem"
Cohesion: 0.13
Nodes (15): wifi_promiscuous_pkt_type_t, SnifferQueueItem, bssid, isBeacon, isDeauthFrame, isHandshakeFrame, packet, raw_len (+7 more)

### Community 149 - "ble_common.cpp"
Cohesion: 0.19
Nodes (11): drawBLE_beacon(), AdvertisedDeviceCallbacks, ble_info(), ble_test(), BLEServer, BLEServerCallbacks, String, disPlayBLESend() (+3 more)

### Community 150 - "net_utils.cpp"
Cohesion: 0.20
Nodes (12): String, getManufacturer(), internetConnection(), ipToString(), MAC(), macToString(), stringToMAC(), clientSnifferCallback() (+4 more)

### Community 151 - "fillInfo"
Cohesion: 0.24
Nodes (12): show, autoMode2String(), String, wifi_ap_record_t, wifi_auth_mode_t, cypherType2String(), displayAPInfo(), fillInfo() (+4 more)

### Community 152 - "js_get_path_from_params"
Cohesion: 0.38
Nodes (13): FileParamsJS, js_get_path_from_params(), JSContext, JSValue, native_storageMkdir(), native_storageRead(), native_storageReaddir(), native_storageRemove() (+5 more)

### Community 154 - "emulate"
Cohesion: 0.25
Nodes (14): buildNdefMessageFromStruct(), Adafruit_PN532, NdefMessage, vector, extractNdefMessageFromPageDump(), hexNibble(), parseHexBytesAfterColon(), emulate (+6 more)

### Community 155 - "enableNaptWhenAccessPointReady"
Cohesion: 0.18
Nodes (14): accessPointNetifUp(), CleanupAction, esp_err_t, IPAddress, DnsStatus, ok, server, tested (+6 more)

### Community 156 - "I2CPins"
Cohesion: 0.18
Nodes (6): setI2CPins, validateI2CPins, JsonObject, I2CPins, scl, sda

### Community 157 - "StartupApp::StartupApp"
Cohesion: 0.26
Nodes (10): StartupApp::StartupApp(), FS, Option, String, vector, getScriptsFolder(), getScriptsOptionsList(), run_bjs_script() (+2 more)

### Community 158 - "setup"
Cohesion: 0.27
Nodes (10): Host, IPAddress, HostInfo, client_connect, client_connected, client_stop, HostInfo::HostInfo(), setup (+2 more)

### Community 159 - "BleSpamEditState"
Cohesion: 0.18
Nodes (12): BleSpamMacRandMode, bleSpamClampMacMode(), BleSpamEditState, adv_backup, edit_row, editing, gap_backup, mac_backup (+4 more)

### Community 160 - "Opt_Coord"
Cohesion: 0.20
Nodes (12): FileList, Option, vector, drawOptions(), drawSubmenu(), listFiles(), Opt_Coord, bgcolor (+4 more)

### Community 161 - "powerSave.cpp"
Cohesion: 0.23
Nodes (11): panelSleep(), turnOffDisplay(), checkPowerSaveTime(), fadeOutScreen(), sleepModeOff(), sleepModeOn(), sleepCallback(), getBrightness() (+3 more)

### Community 162 - "readDecryptedFile"
Cohesion: 0.32
Nodes (10): FS, String, encryptString(), isValidAscii(), readDecryptedFile(), xorEncryptDecryptMD5(), cmd, decryptFileCallback() (+2 more)

### Community 163 - "musicPlayerUI"
Cohesion: 0.32
Nodes (10): IconType, FS, String, drawButton(), drawProgressBar(), drawVectorIcon(), extractFilename(), formatTime() (+2 more)

### Community 164 - "badusb_js.cpp"
Cohesion: 0.41
Nodes (11): JSContext, JSValue, native_badusbHold(), native_badusbPress(), native_badusbPressRaw(), native_badusbPrint(), native_badusbPrintln(), native_badusbRelease() (+3 more)

### Community 165 - "UILayout"
Cohesion: 0.17
Nodes (11): UILayout, BUTTON_SIZE, BUTTON_SPACING, CONTROLS_HEIGHT, DISPLAY_HEIGHT, HEADER_HEIGHT, MARGIN_X, MARGIN_Y (+3 more)

### Community 166 - "CborCursor"
Cohesion: 0.47
Nodes (3): CborCursor, end, p

### Community 167 - "_bytesToHex"
Cohesion: 0.30
Nodes (12): _bytesToHex(), String, _getNfcaTypeName, _isoDepApdu, _probeEmv, _readDESFireInfo, _readIsoDep, _readNdefT4T (+4 more)

### Community 168 - "loadFile"
Cohesion: 0.22
Nodes (11): createFile, fromFile, fromJson, loadFile, saveFile, setBleName, toJson, JsonDocument (+3 more)

### Community 169 - "wifi_crack_handshake"
Cohesion: 0.25
Nodes (9): resetTftDisplay(), FS, String, extract_ssid_from_beacon(), now_us(), parse_pcap_handshake(), swap32(), wifi_crack_handshake() (+1 more)

### Community 170 - "power_commands.cpp"
Cohesion: 0.35
Nodes (10): powerOff(), cmd, SimpleCLI, createPowerCommand(), createPowerCommands(), createPoweroffCommand(), createRebootCommand(), createSleepCommand() (+2 more)

### Community 171 - "spam.cpp"
Cohesion: 0.25
Nodes (9): checkLittleFsSizeNM(), beacon_task(), String, displaySpamStatus(), generate_random_identity(), loadFacesAndNames(), send_pwnagotchi_beacon(), send_pwnagotchi_beacon_main() (+1 more)

### Community 172 - "helpers.h"
Cohesion: 0.24
Nodes (8): _readFileFromSerial(), _setupPsramFs(), cmd, SimpleCLI, createInterpreterCommands(), jsCallback(), irTxBufferCallback(), rfTxBufferCallback()

### Community 173 - "StartupApp"
Cohesion: 0.24
Nodes (9): String, vector, function, map, String, StartupApp, getAppNames, startApp (+1 more)

### Community 174 - "device_js.cpp"
Cohesion: 0.42
Nodes (10): getBattery(), JSContext, JSValue, native_getBattery(), native_getBatteryDetailed(), native_getBoard(), native_getBruceVersion(), native_getDeviceName() (+2 more)

### Community 175 - "subghz_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_subghzRead(), native_subghzReadRaw(), native_subghzSetFrequency(), native_subghzTransmit(), native_subghzTransmitFile(), native_subghzTxEnd() (+2 more)

### Community 176 - "wifi_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_httpFetch(), native_ipAddress(), native_wifiConnect(), native_wifiConnectDialog(), native_wifiConnected(), native_wifiDisconnect() (+2 more)

### Community 177 - "BatteryService"
Cohesion: 0.20
Nodes (9): battery_handler_task(), BatteryService, battery_char, battery_task_handle, end, setup, BLEServer, NimBLECharacteristic (+1 more)

### Community 178 - "qrcode_menu.cpp"
Cohesion: 0.31
Nodes (9): calculate_crc(), String, crc_ccitt_update(), custom_qrcode_menu(), display_custom_qrcode(), pix_qrcode(), qrcode_display(), remove_custom_qrcode() (+1 more)

### Community 179 - "rf_find_protocol"
Cohesion: 0.25
Nodes (10): RfProtocolDef, String, rf_find_protocol(), rf_flipper_protocol_name(), rf_protocol_at(), rf_protocol_count(), rf_protocol_for_number(), RfProtoAlias (+2 more)

### Community 180 - "PN532ServerCallbacks"
Cohesion: 0.20
Nodes (8): BLEServer, BLEServerCallbacks, NimBLECharacteristic, NimBLECharacteristicCallbacks, NimBLEConnInfo, NimBLEServer, PN532ServerCallbacks, RxCharacteristicCallbacks

### Community 181 - "WordlistReader"
Cohesion: 0.22
Nodes (8): File, WordlistReader, buf, cap, eof, file, len, pos

### Community 182 - "BleSpamAttackType"
Cohesion: 0.27
Nodes (10): BleSpamAttackType, BleSpamAttackOption, label, type, bleSpamGetDeviceCount(), bleSpamHandleCustomNameDevice(), bleSpamLoadCustomNames(), bleSpamPickRandomSelection() (+2 more)

### Community 183 - "EthernetMenu"
Cohesion: 0.27
Nodes (7): EthernetMenu, drawIcon, eth, optionsMenu, start_ethernet, MenuItemInterface, run_arp_scanner()

### Community 184 - "optionsMenu"
Cohesion: 0.27
Nodes (6): MenuItemInterface, RFIDMenu, configMenu, drawIcon, optionsMenu, PN532_SRIX()

### Community 185 - "read"
Cohesion: 0.20
Nodes (10): _notifyCb(), _getNtagVariant, _logOpControl, _probeField, read, _readNtagCounters, _readNtagSignature, _startDiscovery (+2 more)

### Community 186 - "CrackShared"
Cohesion: 0.20
Nodes (10): QueueHandle_t, SemaphoreHandle_t, CrackShared, abort, attempts, done_sem, found, found_pw (+2 more)

### Community 187 - "HandshakeData"
Cohesion: 0.20
Nodes (10): HandshakeData, anonce, ap_mac, eapol, eapol_len, mic, snonce, ssid (+2 more)

### Community 188 - "NRF24Menu"
Cohesion: 0.31
Nodes (5): MenuItemInterface, NRF24Menu, configMenu, drawIcon, optionsMenu

### Community 189 - "OthersMenu"
Cohesion: 0.33
Nodes (6): MenuItemInterface, OthersMenu, badUsbHidMenu, drawIcon, micMenu, optionsMenu

### Community 191 - "buffer_js.cpp"
Cohesion: 0.36
Nodes (5): buffer_decode_base64(), JSContext, JSValue, native_buffer_from(), native_buffer_toString()

### Community 192 - "i2c_js.cpp"
Cohesion: 0.58
Nodes (8): JSContext, JSValue, i2c_require_ready(), native_i2c_begin(), native_i2c_read(), native_i2c_scan(), native_i2c_write(), native_i2c_write_read()

### Community 193 - "menu_js.cpp"
Cohesion: 0.50
Nodes (8): JSContext, JSValue, native_menuDisplayMessage(), native_menuPrintSubtitle(), native_menuPrintTitle(), native_menuShow(), native_menuShowMainBorder(), native_menuShowMainBorderWithTitle()

### Community 194 - "bleSpamMenuUi"
Cohesion: 0.25
Nodes (9): bleSpamClampMs(), bleSpamClampTxPower(), bleSpamGetAttackLabel(), bleSpamGetAttackOptionCount(), bleSpamGetAttackTypeByIndex(), bleSpamLoadConfig(), bleSpamMenuUi(), bleSpamSaveConfig() (+1 more)

### Community 196 - "MifareClassicDump"
Cohesion: 0.22
Nodes (9): MifareClassicDump, blockRead, blocks, keyA, keyAFound, keyB, keyBFound, sectors (+1 more)

### Community 197 - "EapolFrame"
Cohesion: 0.22
Nodes (9): Eapol4WayBuffer, m1, m2, m3, EapolFrame, data, len, timestamp_sec (+1 more)

### Community 198 - "UARTPins"
Cohesion: 0.29
Nodes (5): setUARTPins, validateUARTPins, UARTPins, rx, tx

### Community 199 - "gpio_commands.cpp"
Cohesion: 0.43
Nodes (7): cmd, SimpleCLI, createGpioCommands(), gpioModeCallback(), gpioReadCallback(), gpioSetCallback(), is_free_gpio_pin()

### Community 200 - "wifi_commands.cpp"
Cohesion: 0.36
Nodes (7): cmd, SimpleCLI, createWifiCommands(), listenTCPCallback(), scanHostsCallback(), snifferCallback(), webuiCallback()

### Community 201 - "HmacSha1Pre"
Cohesion: 0.39
Nodes (8): IRAM_ATTR, hmac_sha1_20(), hmac_sha1_20w(), HmacSha1Pre, inner, outer, sha1_transform_20b(), sha1_transform_20w()

### Community 202 - "nrf24_js.cpp"
Cohesion: 0.54
Nodes (7): JSContext, JSValue, native_nrf24Begin(), native_nrf24IsConnected(), native_nrf24Receive(), native_nrf24Send(), native_nrf24SetChannel()

### Community 203 - "serial_js.cpp"
Cohesion: 0.61
Nodes (7): JSContext, JSValue, internal_print_mq(), native_serialCmd(), native_serialPrint(), native_serialPrintln(), native_serialReadln()

### Community 204 - "BruceBLEService"
Cohesion: 0.25
Nodes (6): BruceBLEService, end, mtu, pService, setup, NimBLEService

### Community 205 - "TaskBinding"
Cohesion: 0.25
Nodes (8): PollTaskDef, intervalMs, run, runDueTask(), TaskBinding, arg, run, PollFn

### Community 206 - "PlayerState"
Cohesion: 0.25
Nodes (8): PlayerState, filename, isPaused, isPlaying, lastPauseAction, lastUpdate, loopEnabled, scrollOffset

### Community 207 - "`rf/protocols/` — RF Protocol Definitions (sub-GHz)"
Cohesion: 0.25
Nodes (7): Files (Milestone 1), Preset Alias Table (`.sub`), Protocol coverage, Purpose, References / credits, `rf/protocols/` — RF Protocol Definitions (sub-GHz), Rules

### Community 208 - "channel_analyzer_setup"
Cohesion: 0.36
Nodes (6): ca_draw(), ca_rx_cb(), ca_start_wifi(), ca_stop_wifi(), channel_analyzer_setup(), wifi_promiscuous_pkt_type_t

### Community 209 - "jam_detect.cpp"
Cohesion: 0.36
Nodes (6): wifi_promiscuous_pkt_type_t, jam_detect_setup(), jd_draw(), jd_rx_cb(), jd_start_wifi(), jd_stop_wifi()

### Community 210 - "pcap_hdr_t"
Cohesion: 0.25
Nodes (8): pcap_hdr_t, magic, network, sigfigs, snaplen, thiszone, vmaj, vmin

### Community 211 - "CaptiveRequestHandler"
Cohesion: 0.29
Nodes (5): AsyncWebHandler, CaptiveRequestHandler, handleRequest, _portal, AsyncWebServerRequest

### Community 212 - "BleSpamTxPower"
Cohesion: 0.33
Nodes (7): BleSpamTxPower, esp_power_level_t, bleSpamApplyTxPower(), bleSpamInitAdvertiser(), bleSpamSetMac(), bleSpamTxPowerLabel(), bleSpamTxPowerToLevel()

### Community 213 - "RFMenu"
Cohesion: 0.33
Nodes (4): MenuItemInterface, RFMenu, configMenu, drawIcon

### Community 214 - "sound_commands.cpp"
Cohesion: 0.38
Nodes (6): cmd, SimpleCLI, createSoundCommands(), playCallback(), toneCallback(), ttsCallback()

### Community 215 - "wifiMACMenu"
Cohesion: 0.62
Nodes (6): applyConfiguredMAC(), String, generateRandomMAC(), setCustomMAC(), validateMACFormat(), wifiMACMenu()

### Community 216 - "led_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_ledBlink(), native_ledOff(), native_ledSetBrightness(), native_ledSetColor()

### Community 217 - "math_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_math_acosh(), native_math_asinh(), native_math_atanh(), native_math_is_equal()

### Community 218 - "runtime_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_runtimeIsForeground(), native_runtimeMain(), native_runtimeToBackground(), native_runtimeToForeground()

### Community 219 - "AutoCleanup"
Cohesion: 0.29
Nodes (7): AutoCleanup, AutoCleanup::AutoCleanup(), cleanupFunc, enable, enabled, function, function

### Community 220 - "ElmReply"
Cohesion: 0.29
Nodes (6): WiFiClient, ElmReply, complete, raw, status, ReplyStatus

### Community 221 - "wifi_header_t"
Cohesion: 0.29
Nodes (7): wifi_header_t, addr1, addr2, addr3, duration, frame_ctrl, seq_ctrl

### Community 222 - "socks4Proxy"
Cohesion: 0.52
Nodes (6): WiFiClient, readSocks4Request(), relayLoop(), sendSocks4Reply(), socks4Proxy(), WiFiServer

### Community 223 - "MyCallbacks"
Cohesion: 0.33
Nodes (5): BLECharacteristicCallbacks, NimBLECharacteristic, MyCallbacks, data, NimBLEAttValue

### Community 224 - "setupSdCard"
Cohesion: 0.33
Nodes (6): saveFile, File, selectFile, closeSdCard(), setupSdCard(), ToggleSDCard()

### Community 225 - "wg_setup"
Cohesion: 0.47
Nodes (4): File, parse_config_file(), read_and_parse_file(), wg_setup()

### Community 226 - "ble_js.cpp"
Cohesion: 0.60
Nodes (5): JSContext, JSValue, native_bleAdvertise(), native_bleScan(), native_bleStopAdvertise()

### Community 227 - "DisplayTarget"
Cohesion: 0.33
Nodes (6): DisplayTarget, display, isSprite, sprite, tft_display, tft_sprite

### Community 228 - "APInfo"
Cohesion: 0.33
Nodes (6): APInfo, band, bssid, channel, frequency, is_5ghz

### Community 229 - "PidSupport"
Cohesion: 0.40
Nodes (5): bitset, PidSupport, known, supported, SUPPORT_GROUP_COUNT

### Community 230 - "EMVAID"
Cohesion: 0.40
Nodes (5): EMV_Vendor, EMVAID, aid, name, vendor

### Community 231 - "audio_js.cpp"
Cohesion: 0.60
Nodes (4): JSContext, JSValue, native_playAudioFile(), native_tone()

### Community 232 - "BLESerialCallbacks"
Cohesion: 0.40
Nodes (4): BLESerialCallbacks, NimBLECharacteristic, NimBLECharacteristicCallbacks, NimBLEConnInfo

### Community 233 - "ThrottleMethod"
Cohesion: 0.40
Nodes (5): ThrottleMethod, cmd, pid, shortTag, tag

### Community 234 - "BeaconFrame"
Cohesion: 0.40
Nodes (5): BeaconFrame, data, len, timestamp_sec, timestamp_usec

### Community 235 - "pcaprec_hdr_s"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_s, incl_len, orig_len, ts_sec, ts_usec

### Community 236 - "pcaprec_hdr_t"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_t, incl_len, orig_len, ts_sec, ts_usec

### Community 237 - "setEvilPasswordMode"
Cohesion: 0.33
Nodes (4): setEvilPasswordMode, toJson, EvilPortalPasswordMode, JsonDocument

### Community 239 - "Reading"
Cohesion: 0.50
Nodes (3): Reading, valid, value

### Community 240 - "native_notifyBlink"
Cohesion: 0.67
Nodes (3): JSContext, JSValue, native_notifyBlink()

### Community 241 - "AppleProximityDevice"
Cohesion: 0.67
Nodes (3): AppleProximityDevice, device_id, name

### Community 242 - "BleSpamAppleDevice"
Cohesion: 0.67
Nodes (3): BleSpamAppleDevice, payload_name, ui_name

### Community 243 - "PwEntry"
Cohesion: 0.67
Nodes (3): PwEntry, len, pw

## Knowledge Gaps
- **1205 isolated node(s):** `BruceConfig`, `tft_logger`, `netif`, `tm`, `RfCodes` (+1200 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1776 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **7 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `displayError()` connect `displayError` to `ducky_typer.cpp`, `clients.cpp`, `EspConnection`, `loopOptions`, `BLE_Suite.cpp`, `WDGoWars`, `shark_loop`, `deinitBLE`, `nrf_mousejack.cpp`, `TagOMatic`, `SnifferPacket`, `clicker.cpp`, `ble_common.cpp`, `rf_send.cpp`, `padprintln`, `karma_attack.cpp`, `Wardriving`, `display.cpp`, `readDecryptedFile`, `musicPlayerUI`, `PN532.cpp`, `ObdDashboard`, `PN532KillerTools.cpp`, `wifi_atks.cpp`, `wifi_crack_handshake`, `GPSTracker`, `LoRaRF.cpp`, `EMVReader`, `wifi_repeater.cpp`, `qrcode_menu.cpp`, `mykeyboard.cpp`, `ARPScanner.cpp`, `EthernetMenu`, `structs.h`, `drawMainBorderWithTitle`, `initRfModule`, `displayTextLine`, `dialog_js.cpp`, `drawMainBorder`, `set`, `loopSD`, `DHCPStarvation`, `wifiMACMenu`, `sniffer_setup`, `ibutton.cpp`, `wg_setup`, `u2f.cpp`, `Amiibo`, `wifiConnectMenu`, `MassStorage`, `Wigle`, `MACFlooding`, `EthernetHelper`?**
  _High betweenness centrality (0.180) - this node is a cross-community bridge._
- **Why does `loopOptions()` connect `loopOptions` to `displayError`, `ducky_typer.cpp`, `EspConnection`, `TV-B-Gone.cpp`, `shark_loop`, `nrf_mousejack.cpp`, `RFScan`, `TagOMatic`, `IrRead`, `SnifferPacket`, `fm.cpp`, `rf_bruteforce.cpp`, `karma_attack.cpp`, `rf_send.cpp`, `padprintln`, `StartupApp::StartupApp`, `display.cpp`, `Opt_Coord`, `main.cpp`, `ObdDashboard`, `PN532KillerTools.cpp`, `wifi_atks.cpp`, `MainMenu`, `Pn532ble`, `spam.cpp`, `LoRaRF.cpp`, `EMVReader`, `wifi_repeater.cpp`, `qrcode_menu.cpp`, `mykeyboard.cpp`, `ARPScanner.cpp`, `EthernetMenu`, `optionsMenu`, `brucegotchi_start`, `NRF24Menu`, `OthersMenu`, `rf_raw_record_create`, `initRfModule`, `RFID125`, `menu_js.cpp`, `displayTextLine`, `Timer`, `dialog_js.cpp`, `drawMainBorderWithTitle`, `drawMainBorder`, `loopSD`, `RFMenu`, `wifiMACMenu`, `evil_portal.cpp`, `sniffer_setup`, `ibutton.cpp`, `setupSdCard`, `Amiibo`, `wifiConnectMenu`, `led_control.cpp`, `MassStorage`, `webInterface.cpp`, `ble_ninebot.cpp`, `ConfigMenu`?**
  _High betweenness centrality (0.142) - this node is a cross-community bridge._
- **Why does `loopSD()` connect `loopSD` to `displayError`, `ducky_typer.cpp`, `loopOptions`, `BLE_Suite.cpp`, `M5SysWireAdapter`, `nrf_mousejack.cpp`, `karma_attack.cpp`, `rf_send.cpp`, `RFID2`, `StartupApp::StartupApp`, `display.cpp`, `Opt_Coord`, `readDecryptedFile`, `musicPlayerUI`, `PN532.cpp`, `wifi_atks.cpp`, `ST25R3916.cpp`, `wifi_crack_handshake`, `Pn532ble`, `spam.cpp`, `qrcode_menu.cpp`, `displayTextLine`, `dialog_js.cpp`, `drawMainBorder`, `evil_portal.cpp`, `ibutton.cpp`, `setupSdCard`, `Amiibo`, `MassStorage`, `audio.cpp`?**
  _High betweenness centrality (0.057) - this node is a cross-community bridge._
- **Are the 194 inferred relationships involving `loopOptions()` (e.g. with `beginSend` and `selectFile`) actually correct?**
  _`loopOptions()` has 194 INFERRED edges - model-reasoned connections that need verification._
- **Are the 172 inferred relationships involving `displayError()` (e.g. with `beginEspnow` and `beginSend`) actually correct?**
  _`displayError()` has 172 INFERRED edges - model-reasoned connections that need verification._
- **Are the 123 inferred relationships involving `padprintln()` (e.g. with `receiveFile` and `sendFile`) actually correct?**
  _`padprintln()` has 123 INFERRED edges - model-reasoned connections that need verification._
- **What connects `BruceConfig`, `tft_logger`, `netif` to the rest of the system?**
  _1205 weakly-connected nodes found - possible documentation gaps or missing edges._