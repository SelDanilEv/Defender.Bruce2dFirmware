# Graph Report - src  (2026-09-19)

## Corpus Check
- 391 files · ~382,649 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 5357 nodes · 13057 edges · 248 communities (232 shown, 6 thin omitted)
- Extraction: 79% EXTRACTED · 21% INFERRED · 0% AMBIGUOUS · INFERRED: 2745 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `83f4023f`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- BLE_Suite.h
- BLE_Suite.cpp
- ducky_typer.cpp
- Chameleon
- clients.cpp
- EspConnection
- KarmaRuntimeState
- PN532KillerTools
- NimBLEAddress
- BruceConfig
- karma_attack.cpp
- mykeyboard.cpp
- loopOptions
- TagOMatic
- IrRead
- sniffer.cpp
- RFScan
- ST25R3916
- initRfModule
- display_js.cpp
- config.cpp
- RFID2
- main.cpp
- wifi_repeater.cpp
- tftLogger.cpp
- Wardriving
- displayError
- display.cpp
- ble_spam.cpp
- vector
- EvilPortal
- Pn532ble
- SRIXTool
- EMVReader
- structs.h
- rf_send.cpp
- main_menu.h
- PN532.cpp
- rf_keeloq.cpp
- RFIDInterface
- ActiveBroadcastAttack
- RepeaterState
- ST25R3916.cpp
- padprintln
- wifi_atks.cpp
- FastPairExploitEngine
- globals_js.cpp
- obd_dashboard_setup
- LoRaRF.cpp
- drawMainBorderWithTitle
- nrf_mousejack.cpp
- rf_decoder.cpp
- brucegotchi_start
- ScrollableTextArea
- RFID125
- RfCodes
- BLESerialService
- rfalNfcDevice
- audio.cpp
- dialog_js.cpp
- displayTextLine
- loopSD
- DHCPStarvation
- FastPairCrypto
- BleSpamListMetrics
- SSIDDatabase
- AudioPlayerState
- getFsStorage
- setupSdCard
- rf_commands.cpp
- readSubFile
- themeInfo
- ir_jammer.cpp
- BruceBLEService
- execute
- _emuMfcHandle
- BleSpamRunState
- bus_HAL.cpp
- M5SysWireAdapter
- configPins.cpp
- MainMenu
- mic.cpp
- evil_portal.cpp
- sniffer_setup
- Amiibo
- BruceConfigPins
- displayWarning
- Gif
- led_control.cpp
- pwngrid.cpp
- ibutton.cpp
- rfid_js.cpp
- U2fHidDevice
- u2f.cpp
- ApduCommand
- BruceTheme
- fillInfo
- BleSpamConfig
- ARPScanner
- clicker.cpp
- cli.cpp
- musicPlayerUI
- Wigle
- SPIPins
- FS
- MassStorage
- rfid_commands.cpp
- themeFiles
- webInterface.cpp
- MACFlooding
- gpio_js.cpp
- Timer
- responder.cpp
- EvilPortalEndpoints
- drawMainBorder
- BLE_API
- HIDDeviceProfile
- ARPSpoofer
- EthernetHelper
- updateUi
- processQueuedProbeEvents
- ConfigMenu
- USBSerial
- rf_utils.cpp
- FastPairDeviceInfo
- apdu.h
- nrf_jammer_api.cpp
- ir_commands.cpp
- SnifferPacket
- executeHFPAttackChain
- ARPoisoner
- WDGoWars
- TV-B-Gone.cpp
- shark_loop
- CredentialRecord
- .handleCbor
- String
- nrf_start
- ModuleState
- readDecryptedFile
- JS_IsTypedArray
- fm.cpp
- rf_bruteforce.cpp
- SnifferQueueItem
- wifi_recover.cpp
- utils.cpp
- util_commands.cpp
- js_get_path_from_params
- .handleRegister
- emulate
- I2CPins
- StartupApp::StartupApp
- setup
- Opt_Coord
- ClockMenu
- setup
- badusb_js.cpp
- UILayout
- CborCursor
- _bytesToHex
- WordlistReader
- loadFile
- wifi_crack_handshake
- power_commands.cpp
- spam.cpp
- helpers.h
- subghz_js.cpp
- wifi_js.cpp
- rf_find_protocol
- PN532ServerCallbacks
- WiFiState
- EthernetMenu
- createStorageCommands
- HmacSha1Pre
- device_js.cpp
- qrcode_menu.cpp
- read
- CrackShared
- HandshakeData
- GpsMenu
- OthersMenu
- optionsMenu
- RFMenu
- gpio_commands.cpp
- screen_commands.cpp
- wifi_commands.cpp
- buffer_js.cpp
- i2c_js.cpp
- menu_js.cpp
- showAudioSubMenu
- MifareClassicDump
- EapolFrame
- UARTPins
- IRMenu
- NRF24Menu
- optionsMenu
- nrf24_js.cpp
- serial_js.cpp
- `rf/protocols/` — RF Protocol Definitions (sub-GHz)
- channel_analyzer_setup
- jam_detect.cpp
- pcap_hdr_t
- CaptiveRequestHandler
- ConnectMenu
- ScriptsMenu
- settings_commands.cpp
- wifiMACMenu
- led_js.cpp
- math_js.cpp
- runtime_js.cpp
- BleSpamEditState
- AutoCleanup
- wifi_header_t
- socks4Proxy
- MyCallbacks
- vector
- wg_setup
- ble_js.cpp
- DisplayTarget
- APInfo
- SMBClientState
- set
- sound_commands.cpp
- audio_js.cpp
- MyServerCallbacks
- MicConfig
- clientSnifferCallback
- BeaconFrame
- pcaprec_hdr_s
- pcaprec_hdr_t
- selectPortalTemplate
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
- `goToDeepSleep()` --calls--> `displayWarning()`  [INFERRED]
  src/core/mykeyboard.cpp → src/core/display.cpp
- `nrf_info()` --calls--> `padprintln()`  [INFERRED]
  src/modules/NRF24/nrf_common.cpp → src/core/display.cpp
- `loopOptions()` --calls--> `checkReboot()`  [INFERRED]
  src/core/display.h → src/core/mykeyboard.cpp
- `optionsMenu` --calls--> `PN532_SRIX()`  [INFERRED]
  src/core/menu_items/RFIDMenu.h → src/modules/rfid/srix_tool.cpp
- `addEvilWifiMenu()` --calls--> `keyboard()`  [INFERRED]
  src/core/settings.cpp → src/core/mykeyboard.cpp

## Import Cycles
- None detected.

## Communities (248 total, 6 thin omitted)

### Community 0 - "BLE_Suite.h"
Cohesion: 0.02
Nodes (99): AuthBypassEngine, getSpoofAddress, knownDevices, BLEStateManager, activeClients, bleInitialized, cleanupAllClients, currentDeviceName (+91 more)

### Community 1 - "BLE_Suite.cpp"
Cohesion: 0.05
Nodes (80): TouchFooter(), FastPairVersion, addKnownDevice, AuthBypassEngine::AuthBypassEngine(), BLE_Sniffer(), getActiveClientCount, isBLEActive, BleSuiteMenu() (+72 more)

### Community 2 - "ducky_typer.cpp"
Cohesion: 0.06
Nodes (73): optionsMenu, badusbBufferCallback(), badusbFileCallback(), cmd, DuckyCommandType, HIDInterface, cleanupDuckyBLE(), FS (+65 more)

### Community 3 - "Chameleon"
Cohesion: 0.06
Nodes (76): ChameleonUltra, displaySuccess(), HfTag, LfTag, Chameleon, addOptionSetMode, _battery_set, Chameleon::Chameleon() (+68 more)

### Community 4 - "clients.cpp"
Cohesion: 0.08
Nodes (73): ClientProtocol, Fn, IPAddress, ESPNetifEthernetClient, client_close, connect, connected, appendSessionCommandToLog() (+65 more)

### Community 5 - "EspConnection"
Cohesion: 0.06
Nodes (65): File, String, EspConnection, appendPeerToList, beginEspnow, beginSend, broadcastAddress, createFileMessage (+57 more)

### Community 6 - "KarmaRuntimeState"
Cohesion: 0.03
Nodes (74): ActiveNetwork, AttackConfig, KarmaConfig, KarmaMode, map, QueueHandle_t, TaskHandle_t, KarmaRuntimeState (+66 more)

### Community 7 - "PN532KillerTools"
Cohesion: 0.07
Nodes (68): displayInfo(), drawCreditCard(), drawMfkey32Icon(), drawMfkey64Icon(), printCenterFootnote(), printSubtitle(), IPAddress, String (+60 more)

### Community 8 - "NimBLEAddress"
Cohesion: 0.14
Nodes (70): attemptConnectionWithStrategies(), crashAudioStack, executeAudioAttack, attemptSpoofConnection, exploitAuthBypass, forceRepairing, disable, deinitBLE (+62 more)

### Community 9 - "BruceConfig"
Cohesion: 0.04
Nodes (66): BruceConfig, automaticTimeUpdateViaNTP, badUSBBLEKeyboardLayout, badUSBBLEKeyDelay, badUSBBLEShowOutput, bright, clock24hr, colorInverted (+58 more)

### Community 10 - "karma_attack.cpp"
Cohesion: 0.07
Nodes (65): addHighPrioritySSID, getProgressString, launchAttackForResponse, processProbeResponse, recordResponse, sendBeaconFrame, activePortalCount(), addMACToCache() (+57 more)

### Community 11 - "mykeyboard.cpp"
Cohesion: 0.06
Nodes (59): getComplementaryColor2(), box_t, color, h, key, key_sh, touch_id, w (+51 more)

### Community 12 - "loopOptions"
Cohesion: 0.07
Nodes (63): loopOptions(), setLedEffectDirectionConfig(), setLedEffectSpeedConfig(), advancedMenu, displayUIMenu, pinsMenu, num_keyboard(), addEvilWifiMenu() (+55 more)

### Community 13 - "TagOMatic"
Cohesion: 0.08
Nodes (55): RFID_State, String, displaySmallErrorToast(), RFID_State, set, String, vector, TagOMatic (+47 more)

### Community 14 - "IrRead"
Cohesion: 0.08
Nodes (52): IRrecv, JSContext, JSValue, native_irRead(), native_irReadRaw(), native_irTransmit(), native_irTransmitFile(), decode_results (+44 more)

### Community 15 - "sniffer.cpp"
Cohesion: 0.08
Nodes (51): esp_event_base_t, analyzeFrame(), buildHandshakePath(), cacheBeaconFrame(), classifyEapolMessage(), cleanupStaleBeacons(), copyMac(), copySsidToBuffer() (+43 more)

### Community 16 - "RFScan"
Cohesion: 0.07
Nodes (51): RfCodes, String, vector, display_info(), display_signal_data(), RfCodes, String, rf_clear_nav_state() (+43 more)

### Community 17 - "ST25R3916"
Cohesion: 0.04
Nodes (52): CONNECTION_TYPE, Crypto1State, SPIClass, String, ST25R3916, _connection_type, _discoveryStarted, _emuCipher (+44 more)

### Community 18 - "initRfModule"
Cohesion: 0.08
Nodes (46): rfKeeloqTxCallback(), rfSendCallback(), rfTxByNameCallback(), rfTxCallback(), rf_raw_emit(), begin, end, rmt_channel_t (+38 more)

### Community 19 - "display_js.cpp"
Cohesion: 0.15
Nodes (49): JSContext, JSValue, get_display(), get_display_target(), native_color(), native_createSprite(), native_deleteSprite(), native_drawArc() (+41 more)

### Community 20 - "config.cpp"
Cohesion: 0.06
Nodes (35): addDisabledMenu, addEvilWifiName, addMifareKey, addQrCodeEntry, addWebUISession, addWifiCredential, ensureMifareKeysLoaded, ensureRepeaterApCredentials (+27 more)

### Community 21 - "RFID2"
Cohesion: 0.08
Nodes (40): MFRC522, MFRC522DriverPinSimple, BruceMFRC522DriverI2C, _slaveAdr, byte, MFRC522Driver, String, TwoWire (+32 more)

### Community 22 - "main.cpp"
Cohesion: 0.06
Nodes (32): AnimatedGIF, panelSleep(), turnOffDisplay(), checkPowerSaveTime(), fadeOutScreen(), sleepModeOff(), sleepModeOn(), sleepCallback() (+24 more)

### Community 23 - "wifi_repeater.cpp"
Cohesion: 0.10
Nodes (44): ApMenuResult, ConnectAttemptResult, accessPointNetifUp(), applyAccessPointCredentials(), attemptUpstreamConnect(), cancelAndCleanup(), chooseUpstream(), clearRepeaterState() (+36 more)

### Community 24 - "tftLogger.cpp"
Cohesion: 0.05
Nodes (14): String, tft_logger::drawCentreString(), tft_logger::drawRightString(), tft_logger::drawString(), tft_logger::imageToBin(), tft_logger::isLogEqual(), tft_logger::log_drawString(), tft_logger::log_print() (+6 more)

### Community 25 - "Wardriving"
Cohesion: 0.07
Nodes (43): String, wifi_auth_mode_t, HardwareSerial, set, String, TinyGPSPlus, parseMacToU64(), Wardriving (+35 more)

### Community 26 - "displayError"
Cohesion: 0.09
Nodes (40): arduino_event_id_t, arduino_event_info_t, displayError(), drawBLE_beacon(), padprint(), keyboard(), radioHasMemForBle(), radioHasMemForWifi() (+32 more)

### Community 27 - "display.cpp"
Cohesion: 0.09
Nodes (37): buildPngBinPath(), File, FS, String, displayMessage(), displayRedStripe(), drawBatteryStatus(), drawBLESmall() (+29 more)

### Community 28 - "ble_spam.cpp"
Cohesion: 0.09
Nodes (42): BLEAdvertisementData, BleSpamAttackType, BleSpamMacRandMode, EBLEPayloadType, BleSpamAttackOption, label, type, bleSpamBuildAdvertisementData() (+34 more)

### Community 29 - "vector"
Cohesion: 0.05
Nodes (40): map, vector, String, vector, function, map, String, StartupApp (+32 more)

### Community 30 - "EvilPortal"
Cohesion: 0.05
Nodes (38): AsyncWebServer, DNSServer, EvilPortal, apGateway, apName, _autoMode, _autoTemplateFile, _backgroundMode (+30 more)

### Community 31 - "Pn532ble"
Cohesion: 0.08
Nodes (38): String, vector, AppMode, String, vector, Pn532ble, buffer, currentMode (+30 more)

### Community 32 - "SRIXTool"
Cohesion: 0.10
Nodes (38): getColorVariation(), FS, SRIX_State, String, SRIX_State, PN532_SRIX(), SRIXTool, current_state (+30 more)

### Community 33 - "EMVReader"
Cohesion: 0.11
Nodes (36): EMV_Vendor, BinToAscii(), string, vector, EMVAID, aid, name, vendor (+28 more)

### Community 34 - "structs.h"
Cohesion: 0.06
Nodes (25): rf_raw_emit_draw(), rf_listen(), rf_listen_beep(), RfCodes, FreqFound, freq, rssi, HighLow (+17 more)

### Community 35 - "rf_send.cpp"
Cohesion: 0.09
Nodes (30): decimalToHexString(), gpio_num_t, RfProtocolDef, rmt_symbol_word_t, String, vector, rf_encode_protocol(), rf_encoder_selftest() (+22 more)

### Community 36 - "main_menu.h"
Cohesion: 0.08
Nodes (14): MenuItemInterface, BleMenu, configMenu, drawIcon, setBleNameMenu, MenuItemInterface, FileMenu, drawIcon (+6 more)

### Community 37 - "PN532.cpp"
Cohesion: 0.11
Nodes (37): hexToStr(), byte, CONNECTION_TYPE, String, CONNECTION_TYPE, PN532, authenticate_mifare_classic, begin (+29 more)

### Community 38 - "rf_keeloq.cpp"
Cohesion: 0.12
Nodes (35): FS, String, vector, vector, keeloq_build_hop(), keeloq_decrypt(), keeloq_derive_man(), keeloq_embedded_plaintext() (+27 more)

### Community 39 - "RFIDInterface"
Cohesion: 0.07
Nodes (30): String, NdefMessage, PrintableUID, String, vector, RFIDInterface, begin, buildNdefMessage (+22 more)

### Community 40 - "ActiveBroadcastAttack"
Cohesion: 0.06
Nodes (37): ActiveBroadcastAttack, _active, batchStart, broadcastSSID, clearHighPrioritySSIDs, config, currentBatch, currentChannel (+29 more)

### Community 41 - "RepeaterState"
Cohesion: 0.10
Nodes (35): CleanupPlan, actions, count, CleanupAction, RepeaterFailure, RepeaterPhase, failureText(), CleanupAction (+27 more)

### Community 42 - "ST25R3916.cpp"
Cohesion: 0.11
Nodes (35): CONNECTION_TYPE, NdefMessage, vector, _setNfcPower(), st25BuildNdefMessageFromStruct(), st25ExtractNdefMessageFromPageDump(), st25HexNibble(), st25ParseHexBytesAfterColon() (+27 more)

### Community 43 - "padprintln"
Cohesion: 0.10
Nodes (33): padprintf(), padprintln(), File, GPSTracker, add_coord, add_final_file_data, add_initial_file_data, begin_gps (+25 more)

### Community 44 - "wifi_atks.cpp"
Cohesion: 0.13
Nodes (33): esp_err_t, wifiRawTx(), HandshakeTracker, msg1, msg2, msg3, msg4, handshakeUsable() (+25 more)

### Community 45 - "FastPairExploitEngine"
Cohesion: 0.14
Nodes (34): FastPairExploitType, FastPairPopupType, NimBLERemoteCharacteristic, FastPairExploitEngine, createFastPairAdvertisement, discoveredDevices, executeAllExploits, executeCryptoOverflow (+26 more)

### Community 46 - "globals_js.cpp"
Cohesion: 0.17
Nodes (33): JSTimerContextState, JSContext, JSValue, get_timer_state(), js_add_main_timer(), js_clearInterval(), js_clearTimeout(), js_date_now() (+25 more)

### Community 47 - "obd_dashboard_setup"
Cohesion: 0.13
Nodes (29): bitset, WiFiClient, function, String, WiFiClient, isPidUnsupported(), obd_dashboard_setup(), parseBatteryVoltage() (+21 more)

### Community 48 - "LoRaRF.cpp"
Cohesion: 0.10
Nodes (27): MenuItemInterface, LoRaMenu, configMenu, drawIcon, optionsMenu, changeusername(), chfreq(), clearLoraRadio() (+19 more)

### Community 49 - "drawMainBorderWithTitle"
Cohesion: 0.21
Nodes (31): drawMainBorderWithTitle(), stringToMAC(), wifiDisconnect(), buildOptimizedDeauthFrame(), buildTargetListFromScan(), cacheSameSSIDAPs(), Host, vector (+23 more)

### Community 50 - "nrf_mousejack.cpp"
Cohesion: 0.17
Nodes (30): MjDeviceType, MjHidKey, MjTarget, String, mj_addTarget(), mj_asciiToHid(), mj_attackDucky(), mj_attackMenu() (+22 more)

### Community 51 - "rf_decoder.cpp"
Cohesion: 0.10
Nodes (28): RfCodes, RfProtocolDef, rmt_channel_handle_t, rmt_rx_done_event_data_t, rmt_symbol_word_t, vector, QueueHandle_t, rmt_channel_handle_t (+20 more)

### Community 52 - "brucegotchi_start"
Cohesion: 0.10
Nodes (29): BrucePhase, setMood(), advertise(), advertisePhase(), brucegotchi_setup(), brucegotchi_start(), bruceMacToKey(), BruceState (+21 more)

### Community 53 - "ScrollableTextArea"
Cohesion: 0.09
Nodes (30): File, String, String, vector, ScrollableTextArea, clear, firstVisibleLine, _fontSize (+22 more)

### Community 54 - "RFID125"
Cohesion: 0.11
Nodes (28): RFID125_State, String, HardwareSerial, RFID125_State, String, hex2digit(), hex2int(), RFID125 (+20 more)

### Community 55 - "RfCodes"
Cohesion: 0.07
Nodes (29): rmt_symbol_word_t, vector, RawRecording, codeLengths, codes, frequency, gaps, RfCodes (+21 more)

### Community 56 - "BLESerialService"
Cohesion: 0.12
Nodes (23): BLESerialCallbacks, BLESerialService, available, callbacks, end, print, println, read (+15 more)

### Community 57 - "rfalNfcDevice"
Cohesion: 0.15
Nodes (28): _deselectSharedSpiDevices(), _buildEmuMfc, clone, erase, _eraseUltralight, _isUltralightUserPage, _mfcHalt, _mfcRebuildStrAllPages (+20 more)

### Community 58 - "audio.cpp"
Cohesion: 0.20
Nodes (24): AudioOutputI2S, AudioPlaybackInfo, startup_sound(), audioPlaybackTask(), FS, String, createConfiguredAudioOutput(), getAudioPlaybackInfo() (+16 more)

### Community 59 - "dialog_js.cpp"
Cohesion: 0.23
Nodes (26): fromString, JSContext, JSValue, getAreaPointer(), native_dialogChoice(), native_dialogCreateTextViewer(), native_dialogCreateTextViewerClear(), native_dialogCreateTextViewerClose() (+18 more)

### Community 61 - "displayTextLine"
Cohesion: 0.22
Nodes (23): displayTextLine(), addToRecentCodes(), chooseCmdIrFile(), FS, IRCode, String, otherIRcodes(), resetCodesArray() (+15 more)

### Community 62 - "loopSD"
Cohesion: 0.23
Nodes (25): checkExt(), closeSdCard(), copyFile(), copyToFs(), File, FileList, FS, String (+17 more)

### Community 63 - "DHCPStarvation"
Cohesion: 0.12
Nodes (22): dhcp_msg, DHCPStarvation, broadcast_mac_address, change_mac_in_packet, dhcp_payload, ethernet_frame, ipv4_pkt, loop (+14 more)

### Community 64 - "FastPairCrypto"
Cohesion: 0.12
Nodes (23): mbedtls_aes_context, mbedtls_ctr_drbg_context, mbedtls_ecp_group, mbedtls_mpi, FastPairCrypto, aes_ctx, ctr_drbg, d (+15 more)

### Community 65 - "BleSpamListMetrics"
Cohesion: 0.12
Nodes (25): bleSpamEnsureScroll(), bleSpamGetListMetrics(), bleSpamHandleCustomNameDevice(), bleSpamListLoop(), BleSpamListMetrics, footer_y, list_h, list_w (+17 more)

### Community 66 - "SSIDDatabase"
Cohesion: 0.16
Nodes (25): loadNextBatch, restart, setBatchSize, start, File, SSIDDatabase, clearCache, contains (+17 more)

### Community 67 - "AudioPlayerState"
Cohesion: 0.09
Nodes (22): AudioFileSource, AudioGenerator, AudioPlayerState, currentFile, currentGain, generator, mode, mutex (+14 more)

### Community 68 - "getFsStorage"
Cohesion: 0.19
Nodes (23): fromFile, checkLittleFsSize(), getFsStorage(), copyCallback(), cmd, String, crc16(), crc16_update() (+15 more)

### Community 69 - "setupSdCard"
Cohesion: 0.30
Nodes (22): FS, set, String, MifareKeysManager, addKey, appendToFile, appendToFS, clear (+14 more)

### Community 70 - "rf_commands.cpp"
Cohesion: 0.18
Nodes (23): cmd, Command, SimpleCLI, createRfCommands(), createRfKeeloqFileTestCommand(), createRfKeeloqTestCommand(), createRfKeeloqTxCommand(), createRfMfcodesCommand() (+15 more)

### Community 71 - "readSubFile"
Cohesion: 0.12
Nodes (21): rfTxFileCallback(), String, dec2binWzerofill(), hexCharToDecimal(), hexStringToDecimal(), hexStringToU64(), hexStrToBinStr(), FS (+13 more)

### Community 72 - "themeInfo"
Cohesion: 0.08
Nodes (24): themeInfo, ble, boot_img, boot_sound, border, clock, config, connect (+16 more)

### Community 73 - "ir_jammer.cpp"
Cohesion: 0.26
Nodes (23): JammerState, adjustModeSpecificSetting(), cleanupJammer(), IRsend, displayStats(), getFrequency(), getModeName(), handleJammerInput() (+15 more)

### Community 74 - "BruceBLEService"
Cohesion: 0.10
Nodes (16): NimBLEServer, battery_handler_task(), BatteryService, battery_char, battery_task_handle, end, setup, BLEServer (+8 more)

### Community 75 - "execute"
Cohesion: 0.21
Nodes (24): BLEAttackManager, cleanupAfterAttack, connectToDevice, prepareForConnection, profileDevice, testBufferOverflow, testCharacteristicAccess, testServiceDiscovery (+16 more)

### Community 76 - "_emuMfcHandle"
Cohesion: 0.22
Nodes (21): Crypto1State, crypto1_bit(), crypto1_byte(), crypto1_filter(), crypto1_filter_bit(), crypto1_init(), crypto1_parity(), crypto1_swapendian() (+13 more)

### Community 77 - "BleSpamRunState"
Cohesion: 0.09
Nodes (23): BleSpamTxPower, esp_power_level_t, bleSpamApplyTxPower(), bleSpamInitAdvertiser(), BleSpamRunState, adv_active, adv_stop_ms, applied_power (+15 more)

### Community 78 - "bus_HAL.cpp"
Cohesion: 0.16
Nodes (19): acquireI2CBus(), acquireSharedSPI(), acquireSPIBus(), checkAndRecoverSysI2CBus(), gpio_num_t, SemaphoreHandle_t, SPIClass, TwoWire (+11 more)

### Community 79 - "M5SysWireAdapter"
Cohesion: 0.11
Nodes (12): function, lockSysI2CBus(), M5SysWireAdapter, _addr, _error, _freq, _open, _rxbuf (+4 more)

### Community 80 - "configPins.cpp"
Cohesion: 0.13
Nodes (22): factoryReset, setGpsBaudrate, setiButtonPin, setIrRxPin, setIrTxPin, setIrTxRepeats, setRfFreq, setRfFxdFreq (+14 more)

### Community 81 - "MainMenu"
Cohesion: 0.10
Nodes (19): vector, MainMenu, begin, bleMenu, clockMenu, configMenu, connectMenu, _currentIndex (+11 more)

### Community 82 - "mic.cpp"
Cohesion: 0.16
Nodes (21): JSContext, JSValue, native_micCaptureSamples(), native_micRecordWav(), apply_gain_to_buffer(), byte, FS, function (+13 more)

### Community 83 - "evil_portal.cpp"
Cohesion: 0.15
Nodes (22): apName_from_keyboard, beginAP, checkAndExtendDuration, drawScreen, EvilPortal::EvilPortal(), hasCredentials, hasRecentActivity, hasRecentPageView (+14 more)

### Community 84 - "sniffer_setup"
Cohesion: 0.20
Nodes (23): closeDeauthFile(), closeRawFile(), File, FS, TickType_t, deauthCaptureEnabled(), ensureDirectories(), handleDeauthWrite() (+15 more)

### Community 85 - "Amiibo"
Cohesion: 0.15
Nodes (19): Amiibolink, Amiibo, amiibolink, changeUIDMode, checkEmulationTagType, connect, currentMode, delayWithReturn (+11 more)

### Community 86 - "BruceConfigPins"
Cohesion: 0.09
Nodes (21): BruceConfigPins, bleName, filepath, gps_bus, gpsBaudrate, i2c_bus, iButton, irRx (+13 more)

### Community 87 - "displayWarning"
Cohesion: 0.24
Nodes (21): displayWarning(), err_t, _activeLoop(), _deviceActionMenu(), _getStaNetif(), netcutCutAll(), _netcutInputHook(), netcutLoadVipList() (+13 more)

### Community 88 - "Gif"
Cohesion: 0.10
Nodes (17): Gif, closeFile, getLastError, gif, GIFDraw, GifFs, gifPosition, openFile (+9 more)

### Community 89 - "led_control.cpp"
Cohesion: 0.21
Nodes (21): alterOneColorChannel(), beginLed(), blinkLed(), function, hsvToRgb(), ledEffects(), ledPreviewMode(), ledSetup() (+13 more)

### Community 90 - "pwngrid.cpp"
Cohesion: 0.10
Nodes (19): ensureWifiPlatform(), add_new_peer(), checkPwngridGoneFriends(), JsonDocument, String, vector, wifi_promiscuous_pkt_type_t, delete_peer_gone() (+11 more)

### Community 91 - "ibutton.cpp"
Cohesion: 0.18
Nodes (20): IButtonResult, MenuAction, bufferCrcValid(), bufferToHexStr(), byte, String, displayStatus(), doLoad() (+12 more)

### Community 92 - "rfid_js.cpp"
Cohesion: 0.25
Nodes (19): clearSRIXReader(), clearTagReader(), JSContext, JSValue, getSRIXReader(), getTagReader(), native_rfid_AddMifareKey(), native_rfidClear() (+11 more)

### Community 93 - "U2fHidDevice"
Cohesion: 0.10
Nodes (14): mbedtls_ecp_point, U2fHidDevice, _attestationCertDer, _counter, _hid, _masterLoaded, _masterSecret, _nextCid (+6 more)

### Community 94 - "u2f.cpp"
Cohesion: 0.10
Nodes (18): drawU2fStatusScreen(), PendingCommandState, cid, cmd, len, ready, RxMessageState, active (+10 more)

### Community 95 - "ApduCommand"
Cohesion: 0.09
Nodes (22): ApduCommand, C_APDU_CLA, C_APDU_DATA, C_APDU_INS, C_APDU_LC, C_APDU_P1, C_APDU_P1_SELECT_BY_ID, C_APDU_P1_SELECT_BY_NAME (+14 more)

### Community 96 - "BruceTheme"
Cohesion: 0.15
Nodes (18): setUiColor, BruceTheme, bgColor, openThemeFile, priColor, removeTheme, secColor, _setUiColor (+10 more)

### Community 97 - "fillInfo"
Cohesion: 0.16
Nodes (17): String, getManufacturer(), internetConnection(), ipToString(), MAC(), macToString(), autoMode2String(), String (+9 more)

### Community 98 - "BleSpamConfig"
Cohesion: 0.15
Nodes (21): bleSpamAdjustMs(), BleSpamConfig, adv_ms, gap_ms, mac_rand_mode, tx_power, bleSpamConfigScreen(), bleSpamDeinitAdvertiser() (+13 more)

### Community 99 - "ARPScanner"
Cohesion: 0.10
Nodes (17): ARPScanner, arpRequestDelay, esp_net_interface, gateway, hostslist_eth, macStringToByteArray, readArpTableETH, esp_netif_t (+9 more)

### Community 100 - "clicker.cpp"
Cohesion: 0.19
Nodes (16): ClickerConfig, LayoutConfig, MenuItem, cleanupClickerUSB(), clicker_setup(), drawClickingScreen(), drawConfigScreen(), drawMenuItem() (+8 more)

### Community 101 - "cli.cpp"
Cohesion: 0.16
Nodes (6): cmd_error, cliErrorCallback(), SimpleCLI, String, SerialCli, _cli

### Community 102 - "musicPlayerUI"
Cohesion: 0.16
Nodes (19): wakeUpScreen(), IconType, FS, String, drawButton(), drawProgressBar(), drawVectorIcon(), extractFilename() (+11 more)

### Community 103 - "Wigle"
Cohesion: 0.19
Nodes (17): File, FS, String, WiFiClientSecure, String, Wigle, auth_header, _check_token (+9 more)

### Community 104 - "SPIPins"
Cohesion: 0.16
Nodes (17): setCC1101Pins, BruceConfigPins::setLoRaPins(), setNrf24Pins, setPn532Pins, setSDCardPins, setSpiPins, BruceConfigPins::setSR25RPins(), BruceConfigPins::setW5500Pins() (+9 more)

### Community 105 - "FS"
Cohesion: 0.13
Nodes (9): FS, esp_ping_handle_t, ip_addr_t, IPAddress, ping_cb(), ping_cb_fail(), ping_target(), scanLocalHosts() (+1 more)

### Community 106 - "MassStorage"
Cohesion: 0.20
Nodes (13): drawUSBStickIcon(), MassStorage, beginUsb, displayMessage, loop, msc, setup, setupUsbCallback (+5 more)

### Community 107 - "rfid_commands.cpp"
Cohesion: 0.28
Nodes (18): _argTimeout(), cmd, Command, _createRfidModule(), _ensureRfid(), _printTagInfo(), _readTagWithTimeout(), rfidAutotestCallback() (+10 more)

### Community 108 - "themeFiles"
Cohesion: 0.11
Nodes (19): themeFiles, ble, boot_img, boot_sound, clock, config, connect, ethernet (+11 more)

### Community 109 - "webInterface.cpp"
Cohesion: 0.25
Nodes (18): checkUserWebAuth(), cleanlyStopWebUiForWiFiFeature(), color565ToWebHex(), configureWebServer(), AsyncWebServerRequest, FS, String, createDirRecursive() (+10 more)

### Community 110 - "MACFlooding"
Cohesion: 0.17
Nodes (16): eth_hdr, ip_hdr, MACFlooding, calculate_ip_checksum, change_mac_in_packet, eth_header, ethernet_frame, ipv4_pkt (+8 more)

### Community 111 - "gpio_js.cpp"
Cohesion: 0.28
Nodes (18): JSContext, JSValue, native_analogRead(), native_analogWrite(), native_analogWriteFrequency(), native_analogWriteResolution(), native_dacWrite(), native_digitalRead() (+10 more)

### Community 112 - "Timer"
Cohesion: 0.21
Nodes (17): Timer, clearUnderline, drawSoundOption, duration, fontSize, loop, playAlarmPattern, playSoundOnFinish (+9 more)

### Community 113 - "responder.cpp"
Cohesion: 0.19
Nodes (15): buildNTLMType2Msg(), IPAddress, String, decodeNetBIOSLabel(), extractAndPrintHash(), getIPAddress(), getWindowsTimestamp(), handleSMB1() (+7 more)

### Community 114 - "EvilPortalEndpoints"
Cohesion: 0.11
Nodes (17): saveFile, Credential, pwd, user, EvilPortalEndpoints, allowGetCreds, allowSetSsid, getCredsEndpoint (+9 more)

### Community 115 - "drawMainBorder"
Cohesion: 0.39
Nodes (18): drawMainBorder(), addLine, draw, scrollDown, AppMode, hf14aMfReadDumpMode, hf14aMfuReadDumpMode, hf14aMfuWriteDumpMode (+10 more)

### Community 116 - "BLE_API"
Cohesion: 0.15
Nodes (12): BLE_API, battery_service, end, pServer, serial_service, setup, update_mtu, BLEAPICallback (+4 more)

### Community 117 - "HIDDeviceProfile"
Cohesion: 0.11
Nodes (18): HIDDeviceProfile, connectionBehavior, deviceName, hasExistingBond, isAndroidDevice, isAppleDevice, isIoTDevice, isLinuxDevice (+10 more)

### Community 118 - "ARPSpoofer"
Cohesion: 0.15
Nodes (16): ARPSpoofer, arpPCAPfile, gatewayIP, gatewayMAC, loop, mitm, myMAC, pcapFile (+8 more)

### Community 119 - "EthernetHelper"
Cohesion: 0.16
Nodes (14): SPIClass, EthernetHelper, ethEventId, ethNetif, ethSpi, generate_mac, is_connected, mac (+6 more)

### Community 120 - "updateUi"
Cohesion: 0.19
Nodes (12): String, getCurrentMoodFace(), getCurrentMoodId(), getCurrentMoodPhrase(), isCurrentMoodBroken(), String, drawFooterData(), drawMood() (+4 more)

### Community 121 - "processQueuedProbeEvents"
Cohesion: 0.21
Nodes (17): AttackTier, analyzeClientBehavior(), calculateAttackPriority(), determineAttackTier(), enqueuePendingPortal(), getPortalDuration(), getUniqueProbes(), handleBroadcastResponse() (+9 more)

### Community 122 - "ConfigMenu"
Cohesion: 0.21
Nodes (13): ConfigMenu, audioMenu, devMenu, drawIcon, optionsMenu, powerMenu, switchToUARTSerial, switchToUSBSerial (+5 more)

### Community 123 - "USBSerial"
Cohesion: 0.15
Nodes (6): SerialDevice, String, va_list, USBSerial, out, Stream

### Community 124 - "rf_utils.cpp"
Cohesion: 0.15
Nodes (14): _setup_gpio(), String, rf_build_raw(), cc1101ApplyFixedFreqOokPreset(), cc1101ApplyPreciseCalibration(), cc1101InterpolateFsctrl0(), cc1101WaitForIdle(), SPIClass (+6 more)

### Community 125 - "FastPairDeviceInfo"
Cohesion: 0.12
Nodes (17): FastPairDeviceInfo, address, connected, deviceType, modelId, name, rssi, supportsFastPair (+9 more)

### Community 126 - "apdu.h"
Cohesion: 0.20
Nodes (15): appendWscAttr(), string, vector, vector, Ndef, mimeRecord, newMessage, RTD_URI (+7 more)

### Community 127 - "nrf_jammer_api.cpp"
Cohesion: 0.23
Nodes (11): BLEJamMode, nrf_setMode(), NimBLEAddress, isNRF24Available(), jamBLEAdvertisingChannels(), jamBLEChannel(), jamBLEConnectionChannel(), jamDuringConnect() (+3 more)

### Community 128 - "ir_commands.cpp"
Cohesion: 0.24
Nodes (15): cmd, Command, SimpleCLI, createIrCommands(), createIrRxCommand(), createIrTxBufferCommand(), createIrTxCommand(), createIrTxFileCommand() (+7 more)

### Community 129 - "SnifferPacket"
Cohesion: 0.17
Nodes (14): BLE_Sniffer(), BLE_SnifferMenu(), String, vector, parseManufacturerData(), payloadToHex(), SnifferPacket, address (+6 more)

### Community 130 - "executeHFPAttackChain"
Cohesion: 0.30
Nodes (14): showHFPSubMenu(), NimBLEAddress, NimBLEClient, String, vector, HFPExploitEngine, attemptHFPHandshake, attemptHFPPivot (+6 more)

### Community 131 - "ARPoisoner"
Cohesion: 0.17
Nodes (13): ARPoisoner, arpPCAPfile, gatewayIP, gatewayMAC, loop, pcapFile, sendARPPacket, setup (+5 more)

### Community 132 - "WDGoWars"
Cohesion: 0.25
Nodes (13): File, FS, String, WiFiClientSecure, WDGoWars, _check_api_key, _display_banner, host (+5 more)

### Community 133 - "TV-B-Gone.cpp"
Cohesion: 0.26
Nodes (13): IrCode, IRsend, delay_ten_us(), init_ir_tx_mutex(), lock_ir_tx(), quickflashLED(), quickflashLEDx(), read_bits() (+5 more)

### Community 134 - "shark_loop"
Cohesion: 0.23
Nodes (14): checkCollisions(), detectInputs(), displayScore(), drawFish(), drawShark(), Fish, size, x (+6 more)

### Community 135 - "CredentialRecord"
Cohesion: 0.26
Nodes (8): FS, String, CredentialRecord, credId, credIdLen, path, rpIdHash, signCount

### Community 137 - "String"
Cohesion: 0.21
Nodes (16): AsyncWebServerRequest, String, EvilPortal::CaptiveRequestHandler::handleRequest(), creds_GET, credsController, getCapturedPassword, getCapturedSSID, getHtmlTemplate (+8 more)

### Community 138 - "nrf_start"
Cohesion: 0.16
Nodes (8): nrf_info(), nrf_start(), nrf_jammer(), shuffleChannels(), String, nrf_spectrum(), scanChannels(), NRF24_MODE

### Community 139 - "ModuleState"
Cohesion: 0.22
Nodes (13): active(), File, String, escape(), flush(), ModuleState, bytesWritten, file (+5 more)

### Community 140 - "readDecryptedFile"
Cohesion: 0.23
Nodes (12): FS, String, encryptString(), isValidAscii(), readDecryptedFile(), xorEncryptDecryptMD5(), cmd, SimpleCLI (+4 more)

### Community 141 - "JS_IsTypedArray"
Cohesion: 0.26
Nodes (14): JsonVariantConst, native_drawJpg(), buffer_latin1_string_to_bytes(), buffer_latin1_to_string(), JSContext, JSValue, internal_print(), js_fatal_error_handler() (+6 more)

### Community 142 - "fm.cpp"
Cohesion: 0.30
Nodes (13): fm_banner(), fm_begin(), fm_live_run(), fm_options(), fm_options_digit(), fm_options_frq(), fm_scan(), fm_setup() (+5 more)

### Community 143 - "rf_bruteforce.cpp"
Cohesion: 0.18
Nodes (13): BruteProtocol, bits, name, one, pilot, stop, zero, rf_brute_frequency() (+5 more)

### Community 144 - "SnifferQueueItem"
Cohesion: 0.13
Nodes (15): wifi_promiscuous_pkt_type_t, SnifferQueueItem, bssid, isBeacon, isDeauthFrame, isHandshakeFrame, packet, raw_len (+7 more)

### Community 145 - "wifi_recover.cpp"
Cohesion: 0.30
Nodes (13): crack_worker_task(), derive_ptk(), hmac_sha1_precompute(), hmac_sha1_with_pre(), sha1_final(), sha1_init(), sha1_transform(), sha1_update() (+5 more)

### Community 146 - "utils.cpp"
Cohesion: 0.20
Nodes (10): String, TwoWire, formatBytes(), formatTimeDecimal(), getBattery(), getOptionsJSON(), i2c_bulk_write(), printMemoryUsage() (+2 more)

### Community 147 - "util_commands.cpp"
Cohesion: 0.27
Nodes (13): cmd, dateCallback(), displayCallback(), freeCallback(), helpCallback(), i2cCallback(), infoCallback(), loaderCallback() (+5 more)

### Community 148 - "js_get_path_from_params"
Cohesion: 0.38
Nodes (13): FileParamsJS, js_get_path_from_params(), JSContext, JSValue, native_storageMkdir(), native_storageRead(), native_storageReaddir(), native_storageRemove() (+5 more)

### Community 150 - "emulate"
Cohesion: 0.25
Nodes (14): buildNdefMessageFromStruct(), Adafruit_PN532, NdefMessage, vector, extractNdefMessageFromPageDump(), hexNibble(), parseHexBytesAfterColon(), emulate (+6 more)

### Community 151 - "I2CPins"
Cohesion: 0.18
Nodes (6): setI2CPins, validateI2CPins, JsonObject, I2CPins, scl, sda

### Community 152 - "StartupApp::StartupApp"
Cohesion: 0.26
Nodes (10): StartupApp::StartupApp(), FS, Option, String, vector, getScriptsFolder(), getScriptsOptionsList(), run_bjs_script() (+2 more)

### Community 153 - "setup"
Cohesion: 0.27
Nodes (10): Host, IPAddress, HostInfo, client_connect, client_connected, client_stop, HostInfo::HostInfo(), setup (+2 more)

### Community 154 - "Opt_Coord"
Cohesion: 0.18
Nodes (12): FileList, Option, vector, displayScrollingText(), drawOptions(), listFiles(), Opt_Coord, bgcolor (+4 more)

### Community 155 - "ClockMenu"
Cohesion: 0.21
Nodes (9): ClockMenu, drawIcon, optionsMenu, showSubMenu, MenuItemInterface, runClockLoop(), updateClockTimezone(), updateTimeStr() (+1 more)

### Community 156 - "setup"
Cohesion: 0.17
Nodes (12): SimpleCLI, createBadUsbCommands(), SerialCli::SerialCli(), setup, SimpleCLI, createRfidCommands(), SimpleCLI, createSoundCommands() (+4 more)

### Community 157 - "badusb_js.cpp"
Cohesion: 0.41
Nodes (11): JSContext, JSValue, native_badusbHold(), native_badusbPress(), native_badusbPressRaw(), native_badusbPrint(), native_badusbPrintln(), native_badusbRelease() (+3 more)

### Community 158 - "UILayout"
Cohesion: 0.17
Nodes (11): UILayout, BUTTON_SIZE, BUTTON_SPACING, CONTROLS_HEIGHT, DISPLAY_HEIGHT, HEADER_HEIGHT, MARGIN_X, MARGIN_Y (+3 more)

### Community 159 - "CborCursor"
Cohesion: 0.47
Nodes (3): CborCursor, end, p

### Community 160 - "_bytesToHex"
Cohesion: 0.30
Nodes (12): _bytesToHex(), String, _getNfcaTypeName, _isoDepApdu, _probeEmv, _readDESFireInfo, _readIsoDep, _readNdefT4T (+4 more)

### Community 161 - "WordlistReader"
Cohesion: 0.20
Nodes (8): File, WordlistReader, buf, cap, eof, file, len, pos

### Community 162 - "loadFile"
Cohesion: 0.22
Nodes (11): createFile, fromFile, fromJson, loadFile, saveFile, setBleName, toJson, JsonDocument (+3 more)

### Community 163 - "wifi_crack_handshake"
Cohesion: 0.25
Nodes (10): resetTftDisplay(), begin_tft(), FS, String, extract_ssid_from_beacon(), now_us(), parse_pcap_handshake(), swap32() (+2 more)

### Community 164 - "power_commands.cpp"
Cohesion: 0.35
Nodes (10): powerOff(), cmd, SimpleCLI, createPowerCommand(), createPowerCommands(), createPoweroffCommand(), createRebootCommand(), createSleepCommand() (+2 more)

### Community 165 - "spam.cpp"
Cohesion: 0.25
Nodes (9): checkLittleFsSizeNM(), beacon_task(), String, displaySpamStatus(), generate_random_identity(), loadFacesAndNames(), send_pwnagotchi_beacon(), send_pwnagotchi_beacon_main() (+1 more)

### Community 166 - "helpers.h"
Cohesion: 0.24
Nodes (8): _readFileFromSerial(), _setupPsramFs(), cmd, SimpleCLI, createInterpreterCommands(), jsCallback(), irTxBufferCallback(), rfTxBufferCallback()

### Community 167 - "subghz_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_subghzRead(), native_subghzReadRaw(), native_subghzSetFrequency(), native_subghzTransmit(), native_subghzTransmitFile(), native_subghzTxEnd() (+2 more)

### Community 168 - "wifi_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_httpFetch(), native_ipAddress(), native_wifiConnect(), native_wifiConnectDialog(), native_wifiConnected(), native_wifiDisconnect() (+2 more)

### Community 169 - "rf_find_protocol"
Cohesion: 0.25
Nodes (10): RfProtocolDef, String, rf_find_protocol(), rf_flipper_protocol_name(), rf_protocol_at(), rf_protocol_count(), rf_protocol_for_number(), RfProtoAlias (+2 more)

### Community 170 - "PN532ServerCallbacks"
Cohesion: 0.20
Nodes (8): BLEServer, BLEServerCallbacks, NimBLECharacteristic, NimBLECharacteristicCallbacks, NimBLEConnInfo, NimBLEServer, PN532ServerCallbacks, RxCharacteristicCallbacks

### Community 171 - "WiFiState"
Cohesion: 0.18
Nodes (10): String, wifi_mode_t, WiFiState, ap_active, ap_ssid, bssid, channel, ssid (+2 more)

### Community 172 - "EthernetMenu"
Cohesion: 0.27
Nodes (7): EthernetMenu, drawIcon, eth, optionsMenu, start_ethernet, MenuItemInterface, run_arp_scanner()

### Community 173 - "createStorageCommands"
Cohesion: 0.38
Nodes (10): SimpleCLI, createCrc32Command(), createListCommand(), createMd5Command(), createMkdirCommand(), createReadCommand(), createRemoveCommand(), createRmdirCommand() (+2 more)

### Community 174 - "HmacSha1Pre"
Cohesion: 0.36
Nodes (10): IRAM_ATTR, hmac_sha1_20(), hmac_sha1_20w(), HmacSha1Pre, inner, outer, pbkdf2_precomp(), sha1_extract() (+2 more)

### Community 175 - "device_js.cpp"
Cohesion: 0.47
Nodes (9): JSContext, JSValue, native_getBattery(), native_getBatteryDetailed(), native_getBoard(), native_getBruceVersion(), native_getDeviceName(), native_getEEPROMSize() (+1 more)

### Community 176 - "qrcode_menu.cpp"
Cohesion: 0.33
Nodes (8): calculate_crc(), String, crc_ccitt_update(), custom_qrcode_menu(), display_custom_qrcode(), pix_qrcode(), qrcode_display(), remove_custom_qrcode()

### Community 177 - "read"
Cohesion: 0.20
Nodes (10): _notifyCb(), _getNtagVariant, _logOpControl, _probeField, read, _readNtagCounters, _readNtagSignature, _startDiscovery (+2 more)

### Community 178 - "CrackShared"
Cohesion: 0.20
Nodes (10): QueueHandle_t, SemaphoreHandle_t, CrackShared, abort, attempts, done_sem, found, found_pw (+2 more)

### Community 179 - "HandshakeData"
Cohesion: 0.20
Nodes (10): HandshakeData, anonce, ap_mac, eapol, eapol_len, mic, snonce, ssid (+2 more)

### Community 180 - "GpsMenu"
Cohesion: 0.33
Nodes (6): GpsMenu, configMenu, drawIcon, optionsMenu, wardrivingMenu, MenuItemInterface

### Community 181 - "OthersMenu"
Cohesion: 0.33
Nodes (6): MenuItemInterface, OthersMenu, badUsbHidMenu, drawIcon, micMenu, optionsMenu

### Community 182 - "optionsMenu"
Cohesion: 0.31
Nodes (5): MenuItemInterface, RFIDMenu, configMenu, drawIcon, optionsMenu

### Community 183 - "RFMenu"
Cohesion: 0.31
Nodes (5): MenuItemInterface, RFMenu, configMenu, drawIcon, optionsMenu

### Community 184 - "gpio_commands.cpp"
Cohesion: 0.36
Nodes (7): cmd, SimpleCLI, createGpioCommands(), gpioModeCallback(), gpioReadCallback(), gpioSetCallback(), is_free_gpio_pin()

### Community 185 - "screen_commands.cpp"
Cohesion: 0.31
Nodes (7): brightnessCallback(), clockCallback(), cmd, SimpleCLI, createScreenCommands(), hexColorCallback(), rgbColorCallback()

### Community 186 - "wifi_commands.cpp"
Cohesion: 0.33
Nodes (7): cmd, listenTCPCallback(), scanHostsCallback(), snifferCallback(), webuiCallback(), wifiCallback(), _setupAP()

### Community 187 - "buffer_js.cpp"
Cohesion: 0.36
Nodes (5): buffer_decode_base64(), JSContext, JSValue, native_buffer_from(), native_buffer_toString()

### Community 188 - "i2c_js.cpp"
Cohesion: 0.58
Nodes (8): JSContext, JSValue, i2c_require_ready(), native_i2c_begin(), native_i2c_read(), native_i2c_scan(), native_i2c_write(), native_i2c_write_read()

### Community 189 - "menu_js.cpp"
Cohesion: 0.50
Nodes (8): JSContext, JSValue, native_menuDisplayMessage(), native_menuPrintSubtitle(), native_menuPrintTitle(), native_menuShow(), native_menuShowMainBorder(), native_menuShowMainBorderWithTitle()

### Community 190 - "showAudioSubMenu"
Cohesion: 0.42
Nodes (9): AudioAttackService, attackAudioMedia, attackAVRCP, attackTelephony, findAndAttackAudioServices, injectMediaCommands, runMediaCommandHijack(), showAudioSubMenu() (+1 more)

### Community 192 - "MifareClassicDump"
Cohesion: 0.22
Nodes (9): MifareClassicDump, blockRead, blocks, keyA, keyAFound, keyB, keyBFound, sectors (+1 more)

### Community 193 - "EapolFrame"
Cohesion: 0.22
Nodes (9): Eapol4WayBuffer, m1, m2, m3, EapolFrame, data, len, timestamp_sec (+1 more)

### Community 194 - "UARTPins"
Cohesion: 0.29
Nodes (5): setUARTPins, validateUARTPins, UARTPins, rx, tx

### Community 195 - "IRMenu"
Cohesion: 0.32
Nodes (5): MenuItemInterface, IRMenu, configMenu, drawIcon, optionsMenu

### Community 196 - "NRF24Menu"
Cohesion: 0.32
Nodes (5): MenuItemInterface, NRF24Menu, configMenu, drawIcon, optionsMenu

### Community 197 - "optionsMenu"
Cohesion: 0.32
Nodes (5): MenuItemInterface, WifiMenu, configMenu, drawIcon, optionsMenu

### Community 198 - "nrf24_js.cpp"
Cohesion: 0.54
Nodes (7): JSContext, JSValue, native_nrf24Begin(), native_nrf24IsConnected(), native_nrf24Receive(), native_nrf24Send(), native_nrf24SetChannel()

### Community 199 - "serial_js.cpp"
Cohesion: 0.61
Nodes (7): JSContext, JSValue, internal_print_mq(), native_serialCmd(), native_serialPrint(), native_serialPrintln(), native_serialReadln()

### Community 200 - "`rf/protocols/` — RF Protocol Definitions (sub-GHz)"
Cohesion: 0.25
Nodes (7): Files (Milestone 1), Preset Alias Table (`.sub`), Protocol coverage, Purpose, References / credits, `rf/protocols/` — RF Protocol Definitions (sub-GHz), Rules

### Community 201 - "channel_analyzer_setup"
Cohesion: 0.36
Nodes (6): ca_draw(), ca_rx_cb(), ca_start_wifi(), ca_stop_wifi(), channel_analyzer_setup(), wifi_promiscuous_pkt_type_t

### Community 202 - "jam_detect.cpp"
Cohesion: 0.36
Nodes (6): wifi_promiscuous_pkt_type_t, jam_detect_setup(), jd_draw(), jd_rx_cb(), jd_start_wifi(), jd_stop_wifi()

### Community 203 - "pcap_hdr_t"
Cohesion: 0.25
Nodes (8): pcap_hdr_t, magic, network, sigfigs, snaplen, thiszone, vmaj, vmin

### Community 204 - "CaptiveRequestHandler"
Cohesion: 0.29
Nodes (5): AsyncWebHandler, CaptiveRequestHandler, handleRequest, _portal, AsyncWebServerRequest

### Community 205 - "ConnectMenu"
Cohesion: 0.33
Nodes (4): ConnectMenu, drawIcon, optionsMenu, MenuItemInterface

### Community 206 - "ScriptsMenu"
Cohesion: 0.33
Nodes (4): MenuItemInterface, ScriptsMenu, drawIcon, optionsMenu

### Community 207 - "settings_commands.cpp"
Cohesion: 0.33
Nodes (5): cmd, SimpleCLI, createSettingsCommands(), factoryResetCallback(), settingsCallback()

### Community 208 - "wifiMACMenu"
Cohesion: 0.62
Nodes (6): applyConfiguredMAC(), String, generateRandomMAC(), setCustomMAC(), validateMACFormat(), wifiMACMenu()

### Community 209 - "led_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_ledBlink(), native_ledOff(), native_ledSetBrightness(), native_ledSetColor()

### Community 210 - "math_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_math_acosh(), native_math_asinh(), native_math_atanh(), native_math_is_equal()

### Community 211 - "runtime_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_runtimeIsForeground(), native_runtimeMain(), native_runtimeToBackground(), native_runtimeToForeground()

### Community 212 - "BleSpamEditState"
Cohesion: 0.29
Nodes (7): BleSpamEditState, adv_backup, edit_row, editing, gap_backup, mac_backup, tx_backup

### Community 213 - "AutoCleanup"
Cohesion: 0.29
Nodes (7): AutoCleanup, AutoCleanup::AutoCleanup(), cleanupFunc, enable, enabled, function, function

### Community 214 - "wifi_header_t"
Cohesion: 0.29
Nodes (7): wifi_header_t, addr1, addr2, addr3, duration, frame_ctrl, seq_ctrl

### Community 215 - "socks4Proxy"
Cohesion: 0.52
Nodes (6): WiFiClient, readSocks4Request(), relayLoop(), sendSocks4Reply(), socks4Proxy(), WiFiServer

### Community 216 - "MyCallbacks"
Cohesion: 0.33
Nodes (5): BLECharacteristicCallbacks, NimBLECharacteristic, MyCallbacks, data, NimBLEAttValue

### Community 217 - "vector"
Cohesion: 0.33
Nodes (6): ClientBehavior, getTopResponses, vector, getVulnerableClients(), getAllSSIDs, pair

### Community 218 - "wg_setup"
Cohesion: 0.47
Nodes (4): File, parse_config_file(), read_and_parse_file(), wg_setup()

### Community 219 - "ble_js.cpp"
Cohesion: 0.60
Nodes (5): JSContext, JSValue, native_bleAdvertise(), native_bleScan(), native_bleStopAdvertise()

### Community 220 - "DisplayTarget"
Cohesion: 0.33
Nodes (6): DisplayTarget, display, isSprite, sprite, tft_display, tft_sprite

### Community 221 - "APInfo"
Cohesion: 0.33
Nodes (6): APInfo, band, bssid, channel, frequency, is_5ghz

### Community 222 - "SMBClientState"
Cohesion: 0.33
Nodes (6): WiFiClient, SMBClientState, active, challenge, client, sessionId

### Community 224 - "sound_commands.cpp"
Cohesion: 0.60
Nodes (4): cmd, playCallback(), toneCallback(), ttsCallback()

### Community 225 - "audio_js.cpp"
Cohesion: 0.60
Nodes (4): JSContext, JSValue, native_playAudioFile(), native_tone()

### Community 226 - "MyServerCallbacks"
Cohesion: 0.50
Nodes (3): BLEServer, BLEServerCallbacks, MyServerCallbacks

### Community 227 - "MicConfig"
Cohesion: 0.40
Nodes (4): MicConfig, gain, record_time_ms, stealth_mode

### Community 228 - "clientSnifferCallback"
Cohesion: 0.40
Nodes (5): clientSnifferCallback(), String, wifi_promiscuous_pkt_type_t, getVendorFromMAC(), MAC

### Community 229 - "BeaconFrame"
Cohesion: 0.40
Nodes (5): BeaconFrame, data, len, timestamp_sec, timestamp_usec

### Community 230 - "pcaprec_hdr_s"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_s, incl_len, orig_len, ts_sec, ts_usec

### Community 231 - "pcaprec_hdr_t"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_t, incl_len, orig_len, ts_sec, ts_usec

### Community 232 - "selectPortalTemplate"
Cohesion: 0.83
Nodes (4): setupLittleFS(), getDisplayName(), loadPortalTemplates(), selectPortalTemplate()

### Community 233 - "native_notifyBlink"
Cohesion: 0.67
Nodes (3): JSContext, JSValue, native_notifyBlink()

### Community 234 - "AppleProximityDevice"
Cohesion: 0.67
Nodes (3): AppleProximityDevice, device_id, name

### Community 235 - "BleSpamAppleDevice"
Cohesion: 0.67
Nodes (3): BleSpamAppleDevice, payload_name, ui_name

### Community 236 - "PwEntry"
Cohesion: 0.67
Nodes (3): PwEntry, len, pw

## Knowledge Gaps
- **1147 isolated node(s):** `out`, `_freq`, `_addr`, `_open`, `_error` (+1142 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1700 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **6 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `loopOptions()` connect `loopOptions` to `SnifferPacket`, `ducky_typer.cpp`, `Chameleon`, `EspConnection`, `TV-B-Gone.cpp`, `PN532KillerTools`, `shark_loop`, `karma_attack.cpp`, `mykeyboard.cpp`, `TagOMatic`, `fm.cpp`, `IrRead`, `rf_bruteforce.cpp`, `RFScan`, `initRfModule`, `main.cpp`, `wifi_repeater.cpp`, `StartupApp::StartupApp`, `Opt_Coord`, `ClockMenu`, `display.cpp`, `displayError`, `Pn532ble`, `SRIXTool`, `EMVReader`, `rf_send.cpp`, `main_menu.h`, `spam.cpp`, `EthernetMenu`, `wifi_atks.cpp`, `obd_dashboard_setup`, `LoRaRF.cpp`, `qrcode_menu.cpp`, `nrf_mousejack.cpp`, `drawMainBorderWithTitle`, `GpsMenu`, `OthersMenu`, `optionsMenu`, `RFMenu`, `brucegotchi_start`, `RFID125`, `dialog_js.cpp`, `menu_js.cpp`, `loopSD`, `displayTextLine`, `IRMenu`, `NRF24Menu`, `optionsMenu`, `ConnectMenu`, `ScriptsMenu`, `wifiMACMenu`, `MainMenu`, `evil_portal.cpp`, `sniffer_setup`, `Amiibo`, `displayWarning`, `led_control.cpp`, `ibutton.cpp`, `selectPortalTemplate`, `webInterface.cpp`, `drawMainBorder`, `ConfigMenu`, `rf_utils.cpp`?**
  _High betweenness centrality (0.154) - this node is a cross-community bridge._
- **Why does `displayError()` connect `displayError` to `SnifferPacket`, `ducky_typer.cpp`, `BLE_Suite.cpp`, `WDGoWars`, `EspConnection`, `shark_loop`, `Chameleon`, `NimBLEAddress`, `PN532KillerTools`, `nrf_start`, `clients.cpp`, `readDecryptedFile`, `loopOptions`, `IrRead`, `TagOMatic`, `karma_attack.cpp`, `initRfModule`, `wifi_repeater.cpp`, `Wardriving`, `display.cpp`, `Pn532ble`, `SRIXTool`, `EMVReader`, `structs.h`, `wifi_crack_handshake`, `PN532.cpp`, `padprintln`, `EthernetMenu`, `wifi_atks.cpp`, `obd_dashboard_setup`, `LoRaRF.cpp`, `drawMainBorderWithTitle`, `nrf_mousejack.cpp`, `dialog_js.cpp`, `displayTextLine`, `loopSD`, `DHCPStarvation`, `getFsStorage`, `readSubFile`, `wifiMACMenu`, `mic.cpp`, `sniffer_setup`, `Amiibo`, `displayWarning`, `wg_setup`, `ibutton.cpp`, `u2f.cpp`, `BruceTheme`, `musicPlayerUI`, `Wigle`, `MassStorage`, `MACFlooding`, `drawMainBorder`, `EthernetHelper`, `nrf_jammer_api.cpp`?**
  _High betweenness centrality (0.136) - this node is a cross-community bridge._
- **Why does `getFsStorage()` connect `getFsStorage` to `ir_commands.cpp`, `SnifferPacket`, `ducky_typer.cpp`, `BLE_Suite.cpp`, `Chameleon`, `EspConnection`, `String`, `karma_attack.cpp`, `mykeyboard.cpp`, `readDecryptedFile`, `TagOMatic`, `RFID2`, `Wardriving`, `displayError`, `Pn532ble`, `SRIXTool`, `EMVReader`, `loadFile`, `_bytesToHex`, `wifi_crack_handshake`, `PN532.cpp`, `rf_keeloq.cpp`, `RFIDInterface`, `ST25R3916.cpp`, `padprintln`, `nrf_mousejack.cpp`, `RFID125`, `loopSD`, `SSIDDatabase`, `readSubFile`, `mic.cpp`, `evil_portal.cpp`, `Amiibo`, `ibutton.cpp`, `sound_commands.cpp`, `selectPortalTemplate`, `drawMainBorder`, `ConfigMenu`?**
  _High betweenness centrality (0.077) - this node is a cross-community bridge._
- **Are the 194 inferred relationships involving `loopOptions()` (e.g. with `beginSend` and `selectFile`) actually correct?**
  _`loopOptions()` has 194 INFERRED edges - model-reasoned connections that need verification._
- **Are the 172 inferred relationships involving `displayError()` (e.g. with `beginEspnow` and `beginSend`) actually correct?**
  _`displayError()` has 172 INFERRED edges - model-reasoned connections that need verification._
- **Are the 123 inferred relationships involving `padprintln()` (e.g. with `receiveFile` and `sendFile`) actually correct?**
  _`padprintln()` has 123 INFERRED edges - model-reasoned connections that need verification._
- **What connects `out`, `_freq`, `_addr` to the rest of the system?**
  _1147 weakly-connected nodes found - possible documentation gaps or missing edges._