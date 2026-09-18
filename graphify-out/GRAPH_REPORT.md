# Graph Report - src  (2026-09-18)

## Corpus Check
- cluster-only mode — file stats not available

## Summary
- 5320 nodes · 12987 edges · 253 communities (231 shown, 11 thin omitted)
- Extraction: 79% EXTRACTED · 21% INFERRED · 0% AMBIGUOUS · INFERRED: 2745 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a84e5154`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- display_js.cpp
- BLE_Suite.h
- clients.cpp
- Chameleon
- BLE_Suite.cpp
- SRIXTool
- TagOMatic
- KarmaRuntimeState
- ScrollableTextArea
- deinitBLE
- karma_attack.cpp
- box_t
- BruceConfig
- EspConnection
- Pn532ble
- loopOptions
- nrf_mousejack.cpp
- sniffer.cpp
- initRfModule
- RFScan
- ST25R3916
- config.cpp
- padprintln
- IrRead
- RFID2
- wifi_repeater.cpp
- ducky_typer.cpp
- tftLogger.cpp
- ble_spam.cpp
- ActiveBroadcastAttack
- EvilPortal
- main_menu.h
- EMVReader
- rf_keeloq.cpp
- PN532.cpp
- RFIDInterface
- rf_decoder.cpp
- RepeaterState
- display.cpp
- PN532KillerTools.cpp
- ST25R3916.cpp
- displayWarning
- GPSTracker
- structs.h
- PN532KillerTools
- rf_send.cpp
- brucegotchi_start
- BackgroundPortal
- rf_raw_record_create
- RFID125
- NimBLEAddress
- MainMenu
- wifi_atks.cpp
- drawMainBorderWithTitle
- ARPScanner.cpp
- BLESerialService
- rfalNfcDevice
- ARPSpoofer
- execute
- M5SysWireAdapter
- displayTextLine
- MassStorage
- getFsStorage
- DHCPStarvation
- FastPairCrypto
- BleSpamListMetrics
- AudioPlayerState
- configPins.cpp
- setupSdCard
- rf_commands.cpp
- themeInfo
- ir_jammer.cpp
- BruceBLEService
- LoRaRF.cpp
- _emuMfcHandle
- GifPosition
- BleSpamRunState
- cli.cpp
- wg_setup
- rf_encoder.cpp
- sniffer_setup
- BruceConfigPins
- powerSave.cpp
- musicPlayerUI
- led_control.cpp
- setup
- mykeyboard.cpp
- audio.cpp
- loopSD
- ibutton.cpp
- mic.cpp
- U2fHidDevice
- u2f.cpp
- ApduCommand
- BleSpamConfig
- dialog_js.cpp
- main.cpp
- ble_ninebot.cpp
- unregisterClient
- evil_portal.cpp
- SSIDDatabase
- displayError
- BruceTheme
- SPIPins
- RFJammer
- rfid_commands.cpp
- themeFiles
- MACFlooding
- gpio_js.cpp
- Wigle
- Timer
- EvilPortalEndpoints
- webInterface.cpp
- BLE_API
- rfid_js.cpp
- EthernetHelper
- updateUi
- processQueuedProbeEvents
- keyboard
- String
- USBSerial
- bus_HAL.cpp
- vector
- wifi_recover.cpp
- ConfigMenu
- util_commands.cpp
- String
- setup
- ir_commands.cpp
- clicker.cpp
- WDGoWars
- TV-B-Gone.cpp
- shark_loop
- CredentialRecord
- .handleCbor
- net_utils.cpp
- ARPoisoner
- fm.cpp
- rf_bruteforce.cpp
- SnifferQueueItem
- serialcmds.cpp
- .handleRegister
- emulate
- UARTPins
- wifiConnectMenu
- readDecryptedFile
- utils.cpp
- ClockMenu
- power_commands.cpp
- badusb_js.cpp
- UILayout
- CborCursor
- _bytesToHex
- wifi_crack_handshake
- spam.cpp
- responder.cpp
- device_js.cpp
- subghz_js.cpp
- wifi_js.cpp
- PN532ServerCallbacks
- WiFiState
- WordlistReader
- EthernetMenu
- OthersMenu
- SnifferPacket
- read
- CrackShared
- HandshakeData
- Opt_Coord
- AutoCleanup
- GpsMenu
- optionsMenu
- helpers.h
- buffer_js.cpp
- i2c_js.cpp
- menu_js.cpp
- rf_find_protocol
- MifareClassicDump
- String
- EapolFrame
- I2CPins
- LoRaMenu
- fillInfo
- obd_dashboard_setup
- optionsMenu
- screen_commands.cpp
- HmacSha1Pre
- FrameInfo
- nrf24_js.cpp
- serial_js.cpp
- `rf/protocols/` — RF Protocol Definitions (sub-GHz)
- channel_analyzer_setup
- BatteryService
- ensureWifiPlatform
- pcap_hdr_t
- CaptiveRequestHandler
- FS
- led_js.cpp
- math_js.cpp
- runtime_js.cpp
- BleSpamEditState
- FastPairDeviceInfo
- wifi_header_t
- socks4Proxy
- MyCallbacks
- BleSpamAttackType
- getMacAddress
- wifiMACMenu
- ble_js.cpp
- DuckyCommandLookup
- APInfo
- HandshakeTracker
- loadFile
- DuckyCombination
- acquireSPIBus
- audio_js.cpp
- rf_listen
- RFMenu
- bleSpamMenuUi
- BeaconFrame
- pcaprec_hdr_s
- pcaprec_hdr_t
- gpio_commands.cpp
- netif
- evil_portal.h
- MicConfig
- native_notifyBlink
- AppleProximityDevice
- BleSpamAppleDevice
- PwEntry
- setEvilPasswordMode
- selectPortalTemplate
- Option
- vector
- saveHfDumpBinFile
- BleSpamTxPower
- toJson
- sound_commands.cpp
- printDeauthStatus
- SMBClientState
- sortList
- BLESerialService.h

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
- `interpreterHandler()` --calls--> `printMemoryUsage()`  [INFERRED]
  src/modules/bjs_interpreter/interpreter.cpp → src/core/utils.cpp
- `setup()` --calls--> `startSerialCommandsHandlerTask()`  [INFERRED]
  src/main.cpp → src/core/serialcmds.cpp
- `wifiRepeater()` --calls--> `isWifiTransitioning()`  [INFERRED]
  src/modules/wifi/wifi_repeater.cpp → src/core/wifi/wifi_common.cpp
- `display_signal_data()` --calls--> `dec2binWzerofill()`  [INFERRED]
  src/modules/rf/rf_scan.cpp → src/core/type_convertion.cpp
- `loopOptions()` --calls--> `checkReboot()`  [INFERRED]
  src/core/display.h → src/core/mykeyboard.cpp

## Import Cycles
- None detected.

## Communities (253 total, 11 thin omitted)

### Community 0 - "display_js.cpp"
Cohesion: 0.05
Nodes (115): FileParamsJS, JsonVariantConst, JSTimerContextState, JSContext, JSValue, DisplayTarget, display, isSprite (+107 more)

### Community 1 - "BLE_Suite.h"
Cohesion: 0.03
Nodes (90): BLEStateManager, activeClients, bleInitialized, cleanupAllClients, currentDeviceName, getCurrentDeviceName, BruceConfig, CharacteristicInfo (+82 more)

### Community 2 - "clients.cpp"
Cohesion: 0.08
Nodes (73): ClientProtocol, Fn, IPAddress, ESPNetifEthernetClient, client_close, connect, connected, appendSessionCommandToLog() (+65 more)

### Community 3 - "Chameleon"
Cohesion: 0.06
Nodes (58): ChameleonUltra, set, HfTag, LfTag, Chameleon, addOptionSetMode, _battery_set, Chameleon::Chameleon() (+50 more)

### Community 4 - "BLE_Suite.cpp"
Cohesion: 0.05
Nodes (75): TouchFooter(), addKnownDevice, AuthBypassEngine::AuthBypassEngine(), BLE_Sniffer(), getActiveClientCount, isBLEActive, BleSuiteMenu(), String (+67 more)

### Community 5 - "SRIXTool"
Cohesion: 0.10
Nodes (34): getColorVariation(), FS, SRIX_State, String, SRIX_State, SRIXTool, current_state, delayWithReturn (+26 more)

### Community 6 - "TagOMatic"
Cohesion: 0.08
Nodes (45): RFID_State, String, displaySmallErrorToast(), RFID_State, set, String, vector, TagOMatic (+37 more)

### Community 7 - "KarmaRuntimeState"
Cohesion: 0.03
Nodes (74): ActiveNetwork, AttackConfig, KarmaConfig, KarmaMode, map, QueueHandle_t, TaskHandle_t, KarmaRuntimeState (+66 more)

### Community 8 - "ScrollableTextArea"
Cohesion: 0.08
Nodes (30): printTitle(), File, String, String, vector, ScrollableTextArea, clear, firstVisibleLine (+22 more)

### Community 9 - "deinitBLE"
Cohesion: 0.11
Nodes (57): exploitAuthBypass, forceRepairing, disable, deinitBLE, confirmAttack(), DoSAttackServiceClass, advertisingSpam, connectionFlood (+49 more)

### Community 10 - "karma_attack.cpp"
Cohesion: 0.10
Nodes (43): launchAttackForResponse, activePortalCount(), checkCloneAttackOpportunities(), checkForAssociations(), checkPendingPortals(), checkPortals(), clearProbes(), FS (+35 more)

### Community 11 - "box_t"
Cohesion: 0.11
Nodes (27): box_t, color, h, key, key_sh, touch_id, w, x (+19 more)

### Community 12 - "BruceConfig"
Cohesion: 0.04
Nodes (62): BruceConfig, automaticTimeUpdateViaNTP, badUSBBLEKeyboardLayout, badUSBBLEKeyDelay, badUSBBLEShowOutput, bright, clock24hr, colorInverted (+54 more)

### Community 13 - "EspConnection"
Cohesion: 0.05
Nodes (63): File, String, EspConnection, appendPeerToList, beginEspnow, beginSend, broadcastAddress, createFileMessage (+55 more)

### Community 14 - "Pn532ble"
Cohesion: 0.10
Nodes (52): drawMainBorder(), checkLetterShortcutPress(), addLine, draw, scrollDown, AppMode, AppMode, String (+44 more)

### Community 15 - "loopOptions"
Cohesion: 0.07
Nodes (62): loopOptions(), setLedEffectDirectionConfig(), setLedEffectSpeedConfig(), advancedMenu, displayUIMenu, pinsMenu, optionsMenu, optionsMenu (+54 more)

### Community 16 - "nrf_mousejack.cpp"
Cohesion: 0.07
Nodes (47): BLEJamMode, MjDeviceType, MjHidKey, MjTarget, nrf_info(), nrf_setMode(), nrf_start(), NimBLEAddress (+39 more)

### Community 17 - "sniffer.cpp"
Cohesion: 0.10
Nodes (43): esp_event_base_t, analyzeFrame(), buildHandshakePath(), cacheBeaconFrame(), classifyEapolMessage(), cleanupStaleBeacons(), copyMac(), copySsidToBuffer() (+35 more)

### Community 18 - "initRfModule"
Cohesion: 0.09
Nodes (34): rfTxCallback(), _setup_gpio(), begin, end, RFJammer::RFJammer(), rf_scan(), RFScan::RFScan(), rfTransmitCode() (+26 more)

### Community 19 - "RFScan"
Cohesion: 0.08
Nodes (50): RfCodes, String, vector, display_info(), display_signal_data(), RfCodes, String, rf_clear_nav_state() (+42 more)

### Community 20 - "ST25R3916"
Cohesion: 0.04
Nodes (52): CONNECTION_TYPE, Crypto1State, SPIClass, String, ST25R3916, _connection_type, _discoveryStarted, _emuCipher (+44 more)

### Community 21 - "config.cpp"
Cohesion: 0.06
Nodes (35): addDisabledMenu, addEvilWifiName, addMifareKey, addQrCodeEntry, addWebUISession, addWifiCredential, ensureMifareKeysLoaded, ensureRepeaterApCredentials (+27 more)

### Community 22 - "padprintln"
Cohesion: 0.06
Nodes (56): padprint(), padprintf(), padprintln(), add_coord, display_banner, dump_gps_data, loop, String (+48 more)

### Community 23 - "IrRead"
Cohesion: 0.08
Nodes (52): IRrecv, JSContext, JSValue, native_irRead(), native_irReadRaw(), native_irTransmit(), native_irTransmitFile(), decode_results (+44 more)

### Community 24 - "RFID2"
Cohesion: 0.08
Nodes (40): MFRC522, MFRC522DriverPinSimple, BruceMFRC522DriverI2C, _slaveAdr, byte, MFRC522Driver, String, TwoWire (+32 more)

### Community 25 - "wifi_repeater.cpp"
Cohesion: 0.10
Nodes (44): ApMenuResult, ConnectAttemptResult, accessPointNetifUp(), applyAccessPointCredentials(), attemptUpstreamConnect(), cancelAndCleanup(), chooseUpstream(), clearRepeaterState() (+36 more)

### Community 26 - "ducky_typer.cpp"
Cohesion: 0.13
Nodes (43): optionsMenu, HIDInterface, cleanupDuckyBLE(), FS, String, vector, ducky_keyboard(), ducky_setup() (+35 more)

### Community 27 - "tftLogger.cpp"
Cohesion: 0.05
Nodes (14): String, tft_logger::drawCentreString(), tft_logger::drawRightString(), tft_logger::drawString(), tft_logger::imageToBin(), tft_logger::isLogEqual(), tft_logger::log_drawString(), tft_logger::log_print() (+6 more)

### Community 28 - "ble_spam.cpp"
Cohesion: 0.16
Nodes (22): BLEAdvertisementData, EBLEPayloadType, bleSpamBuildAdvertisementData(), bleSpamBuildAppleContinuityAdvertisement(), bleSpamBuildContinuityNearbyAction(), bleSpamFastRandomMac(), bleSpamIsCacheable(), bleSpamNextRand64() (+14 more)

### Community 29 - "ActiveBroadcastAttack"
Cohesion: 0.06
Nodes (39): ActiveBroadcastAttack, _active, batchStart, broadcastSSID, clearHighPrioritySSIDs, config, currentBatch, currentChannel (+31 more)

### Community 30 - "EvilPortal"
Cohesion: 0.05
Nodes (37): AsyncWebServer, EvilPortal, apGateway, apName, _autoMode, _autoTemplateFile, _backgroundMode, _baseDurationSec (+29 more)

### Community 31 - "main_menu.h"
Cohesion: 0.06
Nodes (18): MenuItemInterface, ConnectMenu, drawIcon, MenuItemInterface, FileMenu, drawIcon, optionsMenu, MenuItemInterface (+10 more)

### Community 32 - "EMVReader"
Cohesion: 0.11
Nodes (36): EMV_Vendor, BinToAscii(), string, vector, EMVAID, aid, name, vendor (+28 more)

### Community 33 - "rf_keeloq.cpp"
Cohesion: 0.06
Nodes (57): FS, String, vector, vector, keeloq_build_hop(), keeloq_decrypt(), keeloq_derive_man(), keeloq_embedded_plaintext() (+49 more)

### Community 34 - "PN532.cpp"
Cohesion: 0.11
Nodes (37): hexToStr(), byte, CONNECTION_TYPE, String, CONNECTION_TYPE, PN532, authenticate_mifare_classic, begin (+29 more)

### Community 35 - "RFIDInterface"
Cohesion: 0.07
Nodes (26): NdefMessage, PrintableUID, String, vector, RFIDInterface, begin, clone, dataPages (+18 more)

### Community 36 - "rf_decoder.cpp"
Cohesion: 0.14
Nodes (24): RfCodes, RfProtocolDef, rmt_channel_handle_t, rmt_rx_done_event_data_t, rmt_symbol_word_t, String, vector, rf_build_raw() (+16 more)

### Community 37 - "RepeaterState"
Cohesion: 0.10
Nodes (35): CleanupPlan, actions, count, CleanupAction, RepeaterFailure, RepeaterPhase, failureText(), CleanupAction (+27 more)

### Community 38 - "display.cpp"
Cohesion: 0.07
Nodes (32): AnimatedGIF, displayMessage(), drawBatteryStatus(), drawBLESmall(), drawButton(), drawGpsSmall(), drawSdSmall(), drawStatusBar() (+24 more)

### Community 39 - "PN532KillerTools.cpp"
Cohesion: 0.16
Nodes (35): displayInfo(), drawCreditCard(), drawMfkey32Icon(), drawMfkey64Icon(), printCenterFootnote(), printSubtitle(), disableBleDataTransfer, disableTcpDataTransfer (+27 more)

### Community 40 - "ST25R3916.cpp"
Cohesion: 0.11
Nodes (35): CONNECTION_TYPE, NdefMessage, vector, _setNfcPower(), st25BuildNdefMessageFromStruct(), st25ExtractNdefMessageFromPageDump(), st25HexNibble(), st25ParseHexBytesAfterColon() (+27 more)

### Community 41 - "displayWarning"
Cohesion: 0.24
Nodes (21): displayWarning(), err_t, _activeLoop(), _deviceActionMenu(), _getStaNetif(), netcutCutAll(), _netcutInputHook(), netcutLoadVipList() (+13 more)

### Community 42 - "GPSTracker"
Cohesion: 0.10
Nodes (25): File, GPSTracker, add_final_file_data, add_initial_file_data, begin_gps, create_filename, cur_lat, cur_lng (+17 more)

### Community 43 - "structs.h"
Cohesion: 0.07
Nodes (22): QueueHandle_t, rmt_channel_handle_t, rmt_symbol_word_t, RfRxSession, _buf, _bufSymbols, _ch, _m5Isr (+14 more)

### Community 44 - "PN532KillerTools"
Cohesion: 0.06
Nodes (33): IPAddress, String, WiFiClient, PN532KillerTools, connect, _deviceInitialized, displayBanner, _initializationFailed (+25 more)

### Community 45 - "rf_send.cpp"
Cohesion: 0.07
Nodes (36): decimalToHexString(), String, rf_tx_raw_bits(), FS, RfCodes, RfProtocolDef, String, is_volatile_path() (+28 more)

### Community 46 - "brucegotchi_start"
Cohesion: 0.10
Nodes (29): BrucePhase, setMood(), advertise(), advertisePhase(), brucegotchi_setup(), brucegotchi_start(), bruceMacToKey(), BruceState (+21 more)

### Community 47 - "BackgroundPortal"
Cohesion: 0.07
Nodes (30): getStats, BackgroundPortal, capturedPassword, channel, clientFingerprint, hasCreds, instance, lastHeartbeat (+22 more)

### Community 48 - "rf_raw_record_create"
Cohesion: 0.08
Nodes (32): rf_raw_emit(), rf_raw_emit_draw(), rmt_channel_t, rmt_rx_done_event_data_t, rmt_symbol_word_t, vector, record_rmt_rx_done_callback(), rf_durations_to_rmt_symbols() (+24 more)

### Community 49 - "RFID125"
Cohesion: 0.11
Nodes (28): RFID125_State, String, HardwareSerial, RFID125_State, String, hex2digit(), hex2int(), RFID125 (+20 more)

### Community 50 - "NimBLEAddress"
Cohesion: 0.10
Nodes (47): FastPairExploitType, FastPairPopupType, FastPairVersion, NimBLEAddress, NimBLERemoteCharacteristic, detectFastPairVersion(), FastPairExploitEngine, createFastPairAdvertisement (+39 more)

### Community 51 - "MainMenu"
Cohesion: 0.06
Nodes (28): vector, MainMenu, begin, bleMenu, clockMenu, configMenu, connectMenu, _currentIndex (+20 more)

### Community 52 - "wifi_atks.cpp"
Cohesion: 0.17
Nodes (27): esp_err_t, wifiRawTx(), sendDeauthNow(), beaconAttack(), beaconSpamList(), beaconSpamSingle(), capture_handshake(), checkHeap() (+19 more)

### Community 53 - "drawMainBorderWithTitle"
Cohesion: 0.22
Nodes (29): drawMainBorderWithTitle(), buildOptimizedDeauthFrame(), buildTargetListFromScan(), cacheSameSSIDAPs(), Host, vector, deauthAllByChannel(), deauthAllFromScan() (+21 more)

### Community 54 - "ARPScanner.cpp"
Cohesion: 0.10
Nodes (24): esp_ping_handle_t, ip_addr_t, ARPScanner, afterScanOptions, arpRequestDelay, esp_net_interface, gateway, hostslist_eth (+16 more)

### Community 56 - "BLESerialService"
Cohesion: 0.16
Nodes (19): BLESerialService, available, callbacks, end, print, println, read, readStringUntil (+11 more)

### Community 57 - "rfalNfcDevice"
Cohesion: 0.15
Nodes (28): _deselectSharedSpiDevices(), _buildEmuMfc, clone, erase, _eraseUltralight, _isUltralightUserPage, _mfcHalt, _mfcRebuildStrAllPages (+20 more)

### Community 58 - "ARPSpoofer"
Cohesion: 0.13
Nodes (16): ARPSpoofer, arpPCAPfile, gatewayIP, gatewayMAC, loop, mitm, myMAC, pcapFile (+8 more)

### Community 59 - "execute"
Cohesion: 0.21
Nodes (24): BLEAttackManager, cleanupAfterAttack, connectToDevice, prepareForConnection, profileDevice, testBufferOverflow, testCharacteristicAccess, testServiceDiscovery (+16 more)

### Community 60 - "M5SysWireAdapter"
Cohesion: 0.10
Nodes (15): function, SemaphoreHandle_t, lockSysI2CBus(), M5SysWireAdapter, _addr, _error, _freq, _open (+7 more)

### Community 61 - "displayTextLine"
Cohesion: 0.23
Nodes (24): displayTextLine(), addToRecentCodes(), chooseCmdIrFile(), FS, IRCode, String, otherIRcodes(), resetCodesArray() (+16 more)

### Community 62 - "MassStorage"
Cohesion: 0.08
Nodes (33): map, drawUSBStickIcon(), MassStorage, beginUsb, displayMessage, loop, msc, setup (+25 more)

### Community 63 - "getFsStorage"
Cohesion: 0.14
Nodes (33): fromFile, checkLittleFsSize(), getFsStorage(), copyCallback(), cmd, SimpleCLI, String, crc16() (+25 more)

### Community 64 - "DHCPStarvation"
Cohesion: 0.12
Nodes (22): dhcp_msg, DHCPStarvation, broadcast_mac_address, change_mac_in_packet, dhcp_payload, ethernet_frame, ipv4_pkt, loop (+14 more)

### Community 65 - "FastPairCrypto"
Cohesion: 0.11
Nodes (23): mbedtls_aes_context, mbedtls_ctr_drbg_context, mbedtls_ecp_group, mbedtls_mpi, FastPairCrypto, aes_ctx, ctr_drbg, d (+15 more)

### Community 66 - "BleSpamListMetrics"
Cohesion: 0.13
Nodes (21): bleSpamEnsureScroll(), bleSpamGetListMetrics(), bleSpamListLoop(), BleSpamListMetrics, footer_y, list_h, list_w, list_x (+13 more)

### Community 67 - "AudioPlayerState"
Cohesion: 0.09
Nodes (22): AudioFileSource, AudioGenerator, AudioPlayerState, currentFile, currentGain, generator, mode, mutex (+14 more)

### Community 68 - "configPins.cpp"
Cohesion: 0.12
Nodes (22): factoryReset, setGpsBaudrate, setiButtonPin, setIrRxPin, setIrTxPin, setIrTxRepeats, setRfFreq, setRfFxdFreq (+14 more)

### Community 69 - "setupSdCard"
Cohesion: 0.30
Nodes (22): FS, set, String, MifareKeysManager, addKey, appendToFile, appendToFS, clear (+14 more)

### Community 70 - "rf_commands.cpp"
Cohesion: 0.15
Nodes (28): cmd, Command, SimpleCLI, createRfCommands(), createRfKeeloqFileTestCommand(), createRfKeeloqTestCommand(), createRfKeeloqTxCommand(), createRfMfcodesCommand() (+20 more)

### Community 71 - "themeInfo"
Cohesion: 0.08
Nodes (24): themeInfo, ble, boot_img, boot_sound, border, clock, config, connect (+16 more)

### Community 72 - "ir_jammer.cpp"
Cohesion: 0.27
Nodes (22): JammerState, adjustModeSpecificSetting(), cleanupJammer(), IRsend, displayStats(), getFrequency(), getModeName(), handleJammerInput() (+14 more)

### Community 73 - "BruceBLEService"
Cohesion: 0.25
Nodes (6): BruceBLEService, end, mtu, pService, setup, NimBLEService

### Community 74 - "LoRaRF.cpp"
Cohesion: 0.16
Nodes (20): clearLoraRadio(), JsonDocument, SPIClass, String, downpress(), getLoraBusyPin(), getLoraCsPin(), getLoraIrqPin() (+12 more)

### Community 75 - "_emuMfcHandle"
Cohesion: 0.22
Nodes (21): Crypto1State, crypto1_bit(), crypto1_byte(), crypto1_filter(), crypto1_filter_bit(), crypto1_init(), crypto1_parity(), crypto1_swapendian() (+13 more)

### Community 76 - "GifPosition"
Cohesion: 0.50
Nodes (3): GifPosition, x, y

### Community 77 - "BleSpamRunState"
Cohesion: 0.12
Nodes (16): BleSpamRunState, adv_active, adv_stop_ms, applied_power, cached_advertisement, cached_device_index, cached_type, cached_valid (+8 more)

### Community 78 - "cli.cpp"
Cohesion: 0.14
Nodes (6): cmd_error, cliErrorCallback(), SimpleCLI, String, SerialCli, _cli

### Community 79 - "wg_setup"
Cohesion: 0.47
Nodes (4): File, parse_config_file(), read_and_parse_file(), wg_setup()

### Community 80 - "rf_encoder.cpp"
Cohesion: 0.25
Nodes (14): gpio_num_t, RfProtocolDef, rmt_symbol_word_t, vector, rf_encode_protocol(), rf_encoder_selftest(), rf_keeloq_durations(), rf_push_half() (+6 more)

### Community 81 - "sniffer_setup"
Cohesion: 0.19
Nodes (24): checkLittleFsSizeNM(), closeDeauthFile(), closeRawFile(), File, FS, TickType_t, deauthCaptureEnabled(), ensureDirectories() (+16 more)

### Community 82 - "BruceConfigPins"
Cohesion: 0.09
Nodes (21): BruceConfigPins, bleName, filepath, gps_bus, gpsBaudrate, i2c_bus, iButton, irRx (+13 more)

### Community 83 - "powerSave.cpp"
Cohesion: 0.33
Nodes (8): panelSleep(), turnOffDisplay(), checkPowerSaveTime(), fadeOutScreen(), sleepModeOff(), sleepModeOn(), setSleepMode(), taskInputHandler()

### Community 84 - "musicPlayerUI"
Cohesion: 0.16
Nodes (19): wakeUpScreen(), IconType, FS, String, drawButton(), drawProgressBar(), drawVectorIcon(), extractFilename() (+11 more)

### Community 85 - "led_control.cpp"
Cohesion: 0.21
Nodes (21): alterOneColorChannel(), beginLed(), blinkLed(), function, hsvToRgb(), ledEffects(), ledPreviewMode(), ledSetup() (+13 more)

### Community 86 - "setup"
Cohesion: 0.27
Nodes (10): Host, IPAddress, HostInfo, client_connect, client_connected, client_stop, HostInfo::HostInfo(), setup (+2 more)

### Community 87 - "mykeyboard.cpp"
Cohesion: 0.18
Nodes (13): checkReboot(), String, generalKeyboard(), goToDeepSleep(), handleCharacterAdd(), handleDelete(), handleKeyboardSelection(), handleSpaceAdd() (+5 more)

### Community 88 - "audio.cpp"
Cohesion: 0.19
Nodes (24): AudioOutputI2S, AudioPlaybackInfo, startup_sound(), audioPlaybackTask(), FS, String, createConfiguredAudioOutput(), getAudioPlaybackInfo() (+16 more)

### Community 89 - "loopSD"
Cohesion: 0.25
Nodes (24): displayRedStripe(), checkExt(), closeSdCard(), copyFile(), copyToFs(), File, FS, String (+16 more)

### Community 90 - "ibutton.cpp"
Cohesion: 0.18
Nodes (20): IButtonResult, MenuAction, bufferCrcValid(), bufferToHexStr(), byte, String, displayStatus(), doLoad() (+12 more)

### Community 91 - "mic.cpp"
Cohesion: 0.17
Nodes (21): JSContext, JSValue, native_micCaptureSamples(), native_micRecordWav(), apply_gain_to_buffer(), byte, FS, function (+13 more)

### Community 92 - "U2fHidDevice"
Cohesion: 0.10
Nodes (14): mbedtls_ecp_point, U2fHidDevice, _attestationCertDer, _counter, _hid, _masterLoaded, _masterSecret, _nextCid (+6 more)

### Community 93 - "u2f.cpp"
Cohesion: 0.10
Nodes (18): drawU2fStatusScreen(), PendingCommandState, cid, cmd, len, ready, RxMessageState, active (+10 more)

### Community 94 - "ApduCommand"
Cohesion: 0.09
Nodes (22): ApduCommand, C_APDU_CLA, C_APDU_DATA, C_APDU_INS, C_APDU_LC, C_APDU_P1, C_APDU_P1_SELECT_BY_ID, C_APDU_P1_SELECT_BY_NAME (+14 more)

### Community 95 - "BleSpamConfig"
Cohesion: 0.15
Nodes (21): bleSpamAdjustMs(), BleSpamConfig, adv_ms, gap_ms, mac_rand_mode, tx_power, bleSpamConfigScreen(), bleSpamDeinitAdvertiser() (+13 more)

### Community 96 - "dialog_js.cpp"
Cohesion: 0.23
Nodes (26): fromString, JSContext, JSValue, getAreaPointer(), native_dialogChoice(), native_dialogCreateTextViewer(), native_dialogCreateTextViewerClear(), native_dialogCreateTextViewerClose() (+18 more)

### Community 97 - "main.cpp"
Cohesion: 0.14
Nodes (13): restorePersistedClock(), begin_storage(), begin_tft(), boot_screen(), boot_screen_anim(), init_clock(), init_led(), pollEncoder() (+5 more)

### Community 98 - "ble_ninebot.cpp"
Cohesion: 0.15
Nodes (17): BLENinebot, BLENinebot::BLENinebot(), clientDisconnect, loop, redrawMainBorder, setup, buildModelOptions(), NimBLEClient (+9 more)

### Community 99 - "unregisterClient"
Cohesion: 0.09
Nodes (54): attemptConnectionWithStrategies(), AudioAttackService, attackAudioMedia, attackAVRCP, attackTelephony, crashAudioStack, executeAudioAttack, findAndAttackAudioServices (+46 more)

### Community 100 - "evil_portal.cpp"
Cohesion: 0.16
Nodes (19): apName_from_keyboard, beginAP, checkAndExtendDuration, EvilPortal::EvilPortal(), hasCredentials, hasRecentActivity, hasRecentPageView, loadCustomHtml (+11 more)

### Community 101 - "SSIDDatabase"
Cohesion: 0.16
Nodes (25): loadNextBatch, restart, setBatchSize, start, File, SSIDDatabase, clearCache, contains (+17 more)

### Community 102 - "displayError"
Cohesion: 0.06
Nodes (64): Amiibolink, arduino_event_id_t, arduino_event_info_t, receiveFile, sendFile, displayError(), displaySuccess(), progressHandler() (+56 more)

### Community 103 - "BruceTheme"
Cohesion: 0.16
Nodes (18): setUiColor, BruceTheme, bgColor, openThemeFile, priColor, removeTheme, secColor, _setUiColor (+10 more)

### Community 104 - "SPIPins"
Cohesion: 0.16
Nodes (17): setCC1101Pins, BruceConfigPins::setLoRaPins(), setNrf24Pins, setPn532Pins, setSDCardPins, setSpiPins, BruceConfigPins::setSR25RPins(), BruceConfigPins::setW5500Pins() (+9 more)

### Community 105 - "RFJammer"
Cohesion: 0.20
Nodes (20): getComplementaryColor2(), RFJamMode, RFJamMode, RFJammer, display_banner, isCC1101, jamMode, nTransmitterPin (+12 more)

### Community 106 - "rfid_commands.cpp"
Cohesion: 0.28
Nodes (18): _argTimeout(), cmd, Command, _createRfidModule(), _ensureRfid(), _printTagInfo(), _readTagWithTimeout(), rfidAutotestCallback() (+10 more)

### Community 107 - "themeFiles"
Cohesion: 0.11
Nodes (19): themeFiles, ble, boot_img, boot_sound, clock, config, connect, ethernet (+11 more)

### Community 108 - "MACFlooding"
Cohesion: 0.17
Nodes (16): eth_hdr, ip_hdr, MACFlooding, calculate_ip_checksum, change_mac_in_packet, eth_header, ethernet_frame, ipv4_pkt (+8 more)

### Community 109 - "gpio_js.cpp"
Cohesion: 0.28
Nodes (18): JSContext, JSValue, native_analogRead(), native_analogWrite(), native_analogWriteFrequency(), native_analogWriteResolution(), native_dacWrite(), native_digitalRead() (+10 more)

### Community 110 - "Wigle"
Cohesion: 0.19
Nodes (17): File, FS, String, WiFiClientSecure, String, Wigle, auth_header, _check_token (+9 more)

### Community 111 - "Timer"
Cohesion: 0.21
Nodes (17): Timer, clearUnderline, drawSoundOption, duration, fontSize, loop, playAlarmPattern, playSoundOnFinish (+9 more)

### Community 112 - "EvilPortalEndpoints"
Cohesion: 0.11
Nodes (17): saveFile, Credential, pwd, user, EvilPortalEndpoints, allowGetCreds, allowSetSsid, getCredsEndpoint (+9 more)

### Community 113 - "webInterface.cpp"
Cohesion: 0.25
Nodes (18): checkUserWebAuth(), cleanlyStopWebUiForWiFiFeature(), color565ToWebHex(), configureWebServer(), AsyncWebServerRequest, FS, String, createDirRecursive() (+10 more)

### Community 114 - "BLE_API"
Cohesion: 0.15
Nodes (12): BLE_API, battery_service, end, pServer, serial_service, setup, update_mtu, BLEAPICallback (+4 more)

### Community 115 - "rfid_js.cpp"
Cohesion: 0.25
Nodes (19): clearSRIXReader(), clearTagReader(), JSContext, JSValue, getSRIXReader(), getTagReader(), native_rfid_AddMifareKey(), native_rfidClear() (+11 more)

### Community 116 - "EthernetHelper"
Cohesion: 0.16
Nodes (14): SPIClass, EthernetHelper, ethEventId, ethNetif, ethSpi, generate_mac, is_connected, mac (+6 more)

### Community 117 - "updateUi"
Cohesion: 0.08
Nodes (29): String, getCurrentMoodFace(), getCurrentMoodId(), getCurrentMoodPhrase(), isCurrentMoodBroken(), add_new_peer(), checkPwngridGoneFriends(), JsonDocument (+21 more)

### Community 118 - "processQueuedProbeEvents"
Cohesion: 0.16
Nodes (20): AttackTier, ClientBehavior, getTopResponses, analyzeClientBehavior(), calculateAttackPriority(), vector, determineAttackTier(), getPortalDuration() (+12 more)

### Community 119 - "keyboard"
Cohesion: 0.18
Nodes (15): keyboard(), addEvilWifiMenu(), addMifareKeyMenu(), setEvilEndpointCreds(), setEvilEndpointSsid(), calculate_crc(), String, crc_ccitt_update() (+7 more)

### Community 120 - "String"
Cohesion: 0.28
Nodes (15): buildPngBinPath(), File, FS, String, drawBmp(), drawImg(), drawPNG(), drawPngBin() (+7 more)

### Community 121 - "USBSerial"
Cohesion: 0.15
Nodes (6): SerialDevice, String, va_list, USBSerial, out, Stream

### Community 122 - "bus_HAL.cpp"
Cohesion: 0.27
Nodes (13): acquireI2CBus(), checkAndRecoverSysI2CBus(), TwoWire, getSysI2CBus(), releaseBoardI2CBus(), releaseI2CBus(), setSysI2CBus(), sysWireAdapter() (+5 more)

### Community 123 - "vector"
Cohesion: 0.14
Nodes (20): vector, appendWscAttr(), string, vector, vector, Ndef, mimeRecord, newMessage (+12 more)

### Community 124 - "wifi_recover.cpp"
Cohesion: 0.28
Nodes (15): crack_worker_task(), derive_ptk(), hmac_sha1_precompute(), hmac_sha1_with_pre(), pbkdf2_precomp(), sha1_extract(), sha1_final(), sha1_init() (+7 more)

### Community 125 - "ConfigMenu"
Cohesion: 0.18
Nodes (15): ConfigMenu, audioMenu, devMenu, drawIcon, optionsMenu, powerMenu, switchToUARTSerial, switchToUSBSerial (+7 more)

### Community 126 - "util_commands.cpp"
Cohesion: 0.29
Nodes (12): cmd, dateCallback(), displayCallback(), freeCallback(), helpCallback(), infoCallback(), loaderCallback(), navCallback() (+4 more)

### Community 127 - "String"
Cohesion: 0.14
Nodes (22): addHighPrioritySSID, getProgressString, processProbeResponse, recordResponse, addMACToCache(), buildBeaconFrame(), buildEnhancedProbeResponse(), classifyEAPOLMessage() (+14 more)

### Community 128 - "setup"
Cohesion: 0.11
Nodes (19): SimpleCLI, createBadUsbCommands(), SerialCli::SerialCli(), setup, SimpleCLI, createCryptoCommands(), SimpleCLI, createRfidCommands() (+11 more)

### Community 129 - "ir_commands.cpp"
Cohesion: 0.23
Nodes (16): cmd, Command, SimpleCLI, createIrCommands(), createIrRxCommand(), createIrTxBufferCommand(), createIrTxCommand(), createIrTxFileCommand() (+8 more)

### Community 130 - "clicker.cpp"
Cohesion: 0.19
Nodes (16): ClickerConfig, LayoutConfig, MenuItem, cleanupClickerUSB(), clicker_setup(), drawClickingScreen(), drawConfigScreen(), drawMenuItem() (+8 more)

### Community 131 - "WDGoWars"
Cohesion: 0.25
Nodes (13): File, FS, String, WiFiClientSecure, WDGoWars, _check_api_key, _display_banner, host (+5 more)

### Community 132 - "TV-B-Gone.cpp"
Cohesion: 0.22
Nodes (13): IrCode, IRsend, delay_ten_us(), init_ir_tx_mutex(), lock_ir_tx(), quickflashLED(), quickflashLEDx(), read_bits() (+5 more)

### Community 133 - "shark_loop"
Cohesion: 0.23
Nodes (14): checkCollisions(), detectInputs(), displayScore(), drawFish(), drawShark(), Fish, size, x (+6 more)

### Community 134 - "CredentialRecord"
Cohesion: 0.26
Nodes (8): FS, String, CredentialRecord, credId, credIdLen, path, rpIdHash, signCount

### Community 136 - "net_utils.cpp"
Cohesion: 0.20
Nodes (12): String, getManufacturer(), internetConnection(), ipToString(), MAC(), macToString(), stringToMAC(), clientSnifferCallback() (+4 more)

### Community 137 - "ARPoisoner"
Cohesion: 0.17
Nodes (13): ARPoisoner, arpPCAPfile, gatewayIP, gatewayMAC, loop, pcapFile, sendARPPacket, setup (+5 more)

### Community 138 - "fm.cpp"
Cohesion: 0.30
Nodes (13): fm_banner(), fm_begin(), fm_live_run(), fm_options(), fm_options_digit(), fm_options_frq(), fm_scan(), fm_setup() (+5 more)

### Community 139 - "rf_bruteforce.cpp"
Cohesion: 0.18
Nodes (13): BruteProtocol, bits, name, one, pilot, stop, zero, rf_brute_frequency() (+5 more)

### Community 140 - "SnifferQueueItem"
Cohesion: 0.14
Nodes (14): SnifferQueueItem, bssid, isBeacon, isDeauthFrame, isHandshakeFrame, packet, raw_len, saveDeauth (+6 more)

### Community 141 - "serialcmds.cpp"
Cohesion: 0.22
Nodes (8): CmdPacket, text, String, handleSerialCommands(), parseSerialCommand(), _serialCmdsTaskLoop(), startSerialCommandsHandlerTask(), backToMenu()

### Community 143 - "emulate"
Cohesion: 0.25
Nodes (14): buildNdefMessageFromStruct(), Adafruit_PN532, NdefMessage, vector, extractNdefMessageFromPageDump(), hexNibble(), parseHexBytesAfterColon(), emulate (+6 more)

### Community 144 - "UARTPins"
Cohesion: 0.18
Nodes (6): setUARTPins, validateUARTPins, JsonObject, UARTPins, rx, tx

### Community 145 - "wifiConnectMenu"
Cohesion: 0.11
Nodes (31): drawBLE_beacon(), radioHasMemForBle(), radioHasMemForWifi(), radioLargestDmaBlock(), wifiCallback(), checkMAC(), _connectToWifiNetwork(), String (+23 more)

### Community 146 - "readDecryptedFile"
Cohesion: 0.17
Nodes (16): FS, String, encryptString(), isValidAscii(), readDecryptedFile(), xorEncryptDecryptMD5(), cmd, decryptFileCallback() (+8 more)

### Community 147 - "utils.cpp"
Cohesion: 0.23
Nodes (9): String, TwoWire, formatBytes(), formatTimeDecimal(), getOptionsJSON(), i2c_bulk_write(), printMemoryUsage(), repeatString() (+1 more)

### Community 148 - "ClockMenu"
Cohesion: 0.21
Nodes (9): ClockMenu, drawIcon, optionsMenu, showSubMenu, MenuItemInterface, runClockLoop(), updateClockTimezone(), updateTimeStr() (+1 more)

### Community 149 - "power_commands.cpp"
Cohesion: 0.40
Nodes (9): cmd, SimpleCLI, createPowerCommand(), createPowerCommands(), createPoweroffCommand(), createRebootCommand(), createSleepCommand(), rebootCallback() (+1 more)

### Community 150 - "badusb_js.cpp"
Cohesion: 0.41
Nodes (11): JSContext, JSValue, native_badusbHold(), native_badusbPress(), native_badusbPressRaw(), native_badusbPrint(), native_badusbPrintln(), native_badusbRelease() (+3 more)

### Community 151 - "UILayout"
Cohesion: 0.17
Nodes (11): UILayout, BUTTON_SIZE, BUTTON_SPACING, CONTROLS_HEIGHT, DISPLAY_HEIGHT, HEADER_HEIGHT, MARGIN_X, MARGIN_Y (+3 more)

### Community 152 - "CborCursor"
Cohesion: 0.47
Nodes (3): CborCursor, end, p

### Community 153 - "_bytesToHex"
Cohesion: 0.30
Nodes (12): _bytesToHex(), String, _getNfcaTypeName, _isoDepApdu, _probeEmv, _readDESFireInfo, _readIsoDep, _readNdefT4T (+4 more)

### Community 154 - "wifi_crack_handshake"
Cohesion: 0.25
Nodes (9): resetTftDisplay(), FS, String, extract_ssid_from_beacon(), now_us(), parse_pcap_handshake(), swap32(), wifi_crack_handshake() (+1 more)

### Community 155 - "spam.cpp"
Cohesion: 0.29
Nodes (8): beacon_task(), String, displaySpamStatus(), generate_random_identity(), loadFacesAndNames(), send_pwnagotchi_beacon(), send_pwnagotchi_beacon_main(), drawBottomCanvas()

### Community 156 - "responder.cpp"
Cohesion: 0.19
Nodes (15): buildNTLMType2Msg(), IPAddress, String, decodeNetBIOSLabel(), extractAndPrintHash(), getIPAddress(), getWindowsTimestamp(), handleSMB1() (+7 more)

### Community 157 - "device_js.cpp"
Cohesion: 0.42
Nodes (10): getBattery(), JSContext, JSValue, native_getBattery(), native_getBatteryDetailed(), native_getBoard(), native_getBruceVersion(), native_getDeviceName() (+2 more)

### Community 158 - "subghz_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_subghzRead(), native_subghzReadRaw(), native_subghzSetFrequency(), native_subghzTransmit(), native_subghzTransmitFile(), native_subghzTxEnd() (+2 more)

### Community 159 - "wifi_js.cpp"
Cohesion: 0.44
Nodes (10): JSContext, JSValue, native_httpFetch(), native_ipAddress(), native_wifiConnect(), native_wifiConnectDialog(), native_wifiConnected(), native_wifiDisconnect() (+2 more)

### Community 160 - "PN532ServerCallbacks"
Cohesion: 0.20
Nodes (8): BLEServer, BLEServerCallbacks, NimBLECharacteristic, NimBLECharacteristicCallbacks, NimBLEConnInfo, NimBLEServer, PN532ServerCallbacks, RxCharacteristicCallbacks

### Community 161 - "WiFiState"
Cohesion: 0.20
Nodes (10): String, wifi_mode_t, WiFiState, ap_active, ap_ssid, bssid, channel, ssid (+2 more)

### Community 162 - "WordlistReader"
Cohesion: 0.22
Nodes (8): File, WordlistReader, buf, cap, eof, file, len, pos

### Community 163 - "EthernetMenu"
Cohesion: 0.27
Nodes (7): EthernetMenu, drawIcon, eth, optionsMenu, start_ethernet, MenuItemInterface, run_arp_scanner()

### Community 164 - "OthersMenu"
Cohesion: 0.33
Nodes (6): MenuItemInterface, OthersMenu, badUsbHidMenu, drawIcon, micMenu, optionsMenu

### Community 165 - "SnifferPacket"
Cohesion: 0.17
Nodes (14): BLE_Sniffer(), BLE_SnifferMenu(), String, vector, parseManufacturerData(), payloadToHex(), SnifferPacket, address (+6 more)

### Community 166 - "read"
Cohesion: 0.20
Nodes (10): _notifyCb(), _getNtagVariant, _logOpControl, _probeField, read, _readNtagCounters, _readNtagSignature, _startDiscovery (+2 more)

### Community 167 - "CrackShared"
Cohesion: 0.20
Nodes (10): QueueHandle_t, SemaphoreHandle_t, CrackShared, abort, attempts, done_sem, found, found_pw (+2 more)

### Community 168 - "HandshakeData"
Cohesion: 0.20
Nodes (10): HandshakeData, anonce, ap_mac, eapol, eapol_len, mic, snonce, ssid (+2 more)

### Community 169 - "Opt_Coord"
Cohesion: 0.17
Nodes (13): FileList, Option, vector, displayScrollingText(), drawOptions(), listFiles(), Opt_Coord, bgcolor (+5 more)

### Community 170 - "AutoCleanup"
Cohesion: 0.29
Nodes (7): AutoCleanup, AutoCleanup::AutoCleanup(), cleanupFunc, enable, enabled, function, function

### Community 171 - "GpsMenu"
Cohesion: 0.36
Nodes (5): GpsMenu, drawIcon, optionsMenu, wardrivingMenu, MenuItemInterface

### Community 172 - "optionsMenu"
Cohesion: 0.28
Nodes (6): MenuItemInterface, RFIDMenu, configMenu, drawIcon, optionsMenu, PN532_SRIX()

### Community 173 - "helpers.h"
Cohesion: 0.21
Nodes (9): badusbBufferCallback(), badusbFileCallback(), cmd, _readFileFromSerial(), _setupPsramFs(), cmd, SimpleCLI, createInterpreterCommands() (+1 more)

### Community 174 - "buffer_js.cpp"
Cohesion: 0.36
Nodes (5): buffer_decode_base64(), JSContext, JSValue, native_buffer_from(), native_buffer_toString()

### Community 175 - "i2c_js.cpp"
Cohesion: 0.58
Nodes (8): JSContext, JSValue, i2c_require_ready(), native_i2c_begin(), native_i2c_read(), native_i2c_scan(), native_i2c_write(), native_i2c_write_read()

### Community 176 - "menu_js.cpp"
Cohesion: 0.50
Nodes (8): JSContext, JSValue, native_menuDisplayMessage(), native_menuPrintSubtitle(), native_menuPrintTitle(), native_menuShow(), native_menuShowMainBorder(), native_menuShowMainBorderWithTitle()

### Community 178 - "rf_find_protocol"
Cohesion: 0.25
Nodes (10): RfProtocolDef, String, rf_find_protocol(), rf_flipper_protocol_name(), rf_protocol_at(), rf_protocol_count(), rf_protocol_for_number(), RfProtoAlias (+2 more)

### Community 179 - "MifareClassicDump"
Cohesion: 0.22
Nodes (9): MifareClassicDump, blockRead, blocks, keyA, keyAFound, keyB, keyBFound, sectors (+1 more)

### Community 180 - "String"
Cohesion: 0.21
Nodes (16): AsyncWebServerRequest, String, EvilPortal::CaptiveRequestHandler::handleRequest(), creds_GET, credsController, getCapturedPassword, getCapturedSSID, getHtmlTemplate (+8 more)

### Community 181 - "EapolFrame"
Cohesion: 0.22
Nodes (9): Eapol4WayBuffer, m1, m2, m3, EapolFrame, data, len, timestamp_sec (+1 more)

### Community 182 - "I2CPins"
Cohesion: 0.29
Nodes (5): setI2CPins, validateI2CPins, I2CPins, scl, sda

### Community 183 - "LoRaMenu"
Cohesion: 0.22
Nodes (7): MenuItemInterface, LoRaMenu, configMenu, drawIcon, optionsMenu, changeusername(), chfreq()

### Community 184 - "fillInfo"
Cohesion: 0.24
Nodes (12): show, autoMode2String(), String, wifi_ap_record_t, wifi_auth_mode_t, cypherType2String(), displayAPInfo(), fillInfo() (+4 more)

### Community 185 - "obd_dashboard_setup"
Cohesion: 0.58
Nodes (8): String, WiFiClient, isPidUnsupported(), obd_dashboard_setup(), parseBatteryVoltage(), queryPercentPid(), sendAndDrain(), stripFrameChars()

### Community 186 - "optionsMenu"
Cohesion: 0.18
Nodes (11): MenuItemInterface, WifiMenu, configMenu, drawIcon, optionsMenu, cmd, listenTCPCallback(), scanHostsCallback() (+3 more)

### Community 187 - "screen_commands.cpp"
Cohesion: 0.36
Nodes (7): brightnessCallback(), clockCallback(), cmd, SimpleCLI, createScreenCommands(), hexColorCallback(), rgbColorCallback()

### Community 188 - "HmacSha1Pre"
Cohesion: 0.39
Nodes (8): IRAM_ATTR, hmac_sha1_20(), hmac_sha1_20w(), HmacSha1Pre, inner, outer, sha1_transform_20b(), sha1_transform_20w()

### Community 189 - "FrameInfo"
Cohesion: 0.22
Nodes (9): FrameInfo, apAddr, apKey, eapolMsgNum, isBeacon, isDeauth, isEapol, ssid (+1 more)

### Community 190 - "nrf24_js.cpp"
Cohesion: 0.54
Nodes (7): JSContext, JSValue, native_nrf24Begin(), native_nrf24IsConnected(), native_nrf24Receive(), native_nrf24Send(), native_nrf24SetChannel()

### Community 191 - "serial_js.cpp"
Cohesion: 0.61
Nodes (7): JSContext, JSValue, internal_print_mq(), native_serialCmd(), native_serialPrint(), native_serialPrintln(), native_serialReadln()

### Community 192 - "`rf/protocols/` — RF Protocol Definitions (sub-GHz)"
Cohesion: 0.25
Nodes (7): Files (Milestone 1), Preset Alias Table (`.sub`), Protocol coverage, Purpose, References / credits, `rf/protocols/` — RF Protocol Definitions (sub-GHz), Rules

### Community 193 - "channel_analyzer_setup"
Cohesion: 0.36
Nodes (6): ca_draw(), ca_rx_cb(), ca_start_wifi(), ca_stop_wifi(), channel_analyzer_setup(), wifi_promiscuous_pkt_type_t

### Community 194 - "BatteryService"
Cohesion: 0.20
Nodes (9): battery_handler_task(), BatteryService, battery_char, battery_task_handle, end, setup, BLEServer, NimBLECharacteristic (+1 more)

### Community 195 - "ensureWifiPlatform"
Cohesion: 0.27
Nodes (8): ensureWifiPlatform(), initPwngrid(), wifi_promiscuous_pkt_type_t, jam_detect_setup(), jd_draw(), jd_rx_cb(), jd_start_wifi(), jd_stop_wifi()

### Community 196 - "pcap_hdr_t"
Cohesion: 0.25
Nodes (8): pcap_hdr_t, magic, network, sigfigs, snaplen, thiszone, vmaj, vmin

### Community 197 - "CaptiveRequestHandler"
Cohesion: 0.29
Nodes (5): AsyncWebHandler, CaptiveRequestHandler, handleRequest, _portal, AsyncWebServerRequest

### Community 199 - "led_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_ledBlink(), native_ledOff(), native_ledSetBrightness(), native_ledSetColor()

### Community 200 - "math_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_math_acosh(), native_math_asinh(), native_math_atanh(), native_math_is_equal()

### Community 201 - "runtime_js.cpp"
Cohesion: 0.57
Nodes (6): JSContext, JSValue, native_runtimeIsForeground(), native_runtimeMain(), native_runtimeToBackground(), native_runtimeToForeground()

### Community 202 - "BleSpamEditState"
Cohesion: 0.18
Nodes (12): BleSpamMacRandMode, bleSpamClampMacMode(), BleSpamEditState, adv_backup, edit_row, editing, gap_backup, mac_backup (+4 more)

### Community 203 - "FastPairDeviceInfo"
Cohesion: 0.11
Nodes (20): AuthBypassEngine, attemptSpoofConnection, getSpoofAddress, knownDevices, FastPairDeviceInfo, address, connected, deviceType (+12 more)

### Community 204 - "wifi_header_t"
Cohesion: 0.29
Nodes (7): wifi_header_t, addr1, addr2, addr3, duration, frame_ctrl, seq_ctrl

### Community 205 - "socks4Proxy"
Cohesion: 0.52
Nodes (6): WiFiClient, readSocks4Request(), relayLoop(), sendSocks4Reply(), socks4Proxy(), WiFiServer

### Community 206 - "MyCallbacks"
Cohesion: 0.33
Nodes (5): BLECharacteristicCallbacks, NimBLECharacteristic, MyCallbacks, data, NimBLEAttValue

### Community 207 - "BleSpamAttackType"
Cohesion: 0.27
Nodes (10): BleSpamAttackType, BleSpamAttackOption, label, type, bleSpamGetDeviceCount(), bleSpamHandleCustomNameDevice(), bleSpamLoadCustomNames(), bleSpamPickRandomSelection() (+2 more)

### Community 208 - "getMacAddress"
Cohesion: 0.40
Nodes (6): fromJson, setBleName, toJson, JsonObject, String, getMacAddress()

### Community 209 - "wifiMACMenu"
Cohesion: 0.62
Nodes (6): applyConfiguredMAC(), String, generateRandomMAC(), setCustomMAC(), validateMACFormat(), wifiMACMenu()

### Community 210 - "ble_js.cpp"
Cohesion: 0.60
Nodes (5): JSContext, JSValue, native_bleAdvertise(), native_bleScan(), native_bleStopAdvertise()

### Community 211 - "DuckyCommandLookup"
Cohesion: 0.40
Nodes (5): DuckyCommandType, DuckyCommandLookup, command, key, type

### Community 212 - "APInfo"
Cohesion: 0.33
Nodes (6): APInfo, band, bssid, channel, frequency, is_5ghz

### Community 213 - "HandshakeTracker"
Cohesion: 0.33
Nodes (6): HandshakeTracker, msg1, msg2, msg3, msg4, handshakeUsable()

### Community 214 - "loadFile"
Cohesion: 0.50
Nodes (5): createFile, fromFile, loadFile, saveFile, JsonDocument

### Community 215 - "DuckyCombination"
Cohesion: 0.40
Nodes (5): DuckyCombination, command, key1, key2, key3

### Community 216 - "acquireSPIBus"
Cohesion: 0.83
Nodes (4): acquireSharedSPI(), acquireSPIBus(), gpio_num_t, SPIClass

### Community 217 - "audio_js.cpp"
Cohesion: 0.60
Nodes (4): JSContext, JSValue, native_playAudioFile(), native_tone()

### Community 219 - "RFMenu"
Cohesion: 0.33
Nodes (4): MenuItemInterface, RFMenu, configMenu, drawIcon

### Community 220 - "bleSpamMenuUi"
Cohesion: 0.25
Nodes (9): bleSpamClampMs(), bleSpamClampTxPower(), bleSpamGetAttackLabel(), bleSpamGetAttackOptionCount(), bleSpamGetAttackTypeByIndex(), bleSpamLoadConfig(), bleSpamMenuUi(), bleSpamSaveConfig() (+1 more)

### Community 221 - "BeaconFrame"
Cohesion: 0.40
Nodes (5): BeaconFrame, data, len, timestamp_sec, timestamp_usec

### Community 222 - "pcaprec_hdr_s"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_s, incl_len, orig_len, ts_sec, ts_usec

### Community 223 - "pcaprec_hdr_t"
Cohesion: 0.40
Nodes (5): pcaprec_hdr_t, incl_len, orig_len, ts_sec, ts_usec

### Community 224 - "gpio_commands.cpp"
Cohesion: 0.43
Nodes (7): cmd, SimpleCLI, createGpioCommands(), gpioModeCallback(), gpioReadCallback(), gpioSetCallback(), is_free_gpio_pin()

### Community 225 - "netif"
Cohesion: 0.40
Nodes (3): File, sendARPPacket(), netif

### Community 227 - "MicConfig"
Cohesion: 0.40
Nodes (4): MicConfig, gain, record_time_ms, stealth_mode

### Community 228 - "native_notifyBlink"
Cohesion: 0.67
Nodes (3): JSContext, JSValue, native_notifyBlink()

### Community 229 - "AppleProximityDevice"
Cohesion: 0.67
Nodes (3): AppleProximityDevice, device_id, name

### Community 230 - "BleSpamAppleDevice"
Cohesion: 0.67
Nodes (3): BleSpamAppleDevice, payload_name, ui_name

### Community 231 - "PwEntry"
Cohesion: 0.67
Nodes (3): PwEntry, len, pw

### Community 233 - "selectPortalTemplate"
Cohesion: 0.83
Nodes (4): setupLittleFS(), getDisplayName(), loadPortalTemplates(), selectPortalTemplate()

### Community 239 - "saveHfDumpBinFile"
Cohesion: 0.67
Nodes (3): String, vector, saveHfDumpBinFile

### Community 245 - "BleSpamTxPower"
Cohesion: 0.33
Nodes (7): BleSpamTxPower, esp_power_level_t, bleSpamApplyTxPower(), bleSpamInitAdvertiser(), bleSpamSetMac(), bleSpamTxPowerLabel(), bleSpamTxPowerToLevel()

### Community 247 - "sound_commands.cpp"
Cohesion: 0.60
Nodes (4): cmd, playCallback(), toneCallback(), ttsCallback()

### Community 249 - "SMBClientState"
Cohesion: 0.33
Nodes (6): WiFiClient, SMBClientState, active, challenge, client, sessionId

### Community 251 - "BLESerialService.h"
Cohesion: 0.20
Nodes (5): NimBLEServer, BLESerialCallbacks, NimBLECharacteristic, NimBLECharacteristicCallbacks, NimBLEConnInfo

## Knowledge Gaps
- **1133 isolated node(s):** `BruceConfig`, `tft_logger`, `netif`, `RfCodes`, `tm` (+1128 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1682 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **11 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `displayError()` connect `displayError` to `clients.cpp`, `WDGoWars`, `BLE_Suite.cpp`, `shark_loop`, `SRIXTool`, `TagOMatic`, `karma_attack.cpp`, `EspConnection`, `Pn532ble`, `loopOptions`, `nrf_mousejack.cpp`, `wifiConnectMenu`, `readDecryptedFile`, `initRfModule`, `RFScan`, `padprintln`, `IrRead`, `wifi_repeater.cpp`, `ducky_typer.cpp`, `wifi_crack_handshake`, `EMVReader`, `PN532.cpp`, `EthernetMenu`, `SnifferPacket`, `display.cpp`, `PN532KillerTools.cpp`, `displayWarning`, `rf_send.cpp`, `wifi_atks.cpp`, `drawMainBorderWithTitle`, `ARPScanner.cpp`, `LoRaMenu`, `obd_dashboard_setup`, `displayTextLine`, `MassStorage`, `getFsStorage`, `DHCPStarvation`, `LoRaRF.cpp`, `wg_setup`, `wifiMACMenu`, `sniffer_setup`, `musicPlayerUI`, `mykeyboard.cpp`, `loopSD`, `ibutton.cpp`, `mic.cpp`, `rf_listen`, `u2f.cpp`, `dialog_js.cpp`, `unregisterClient`, `BruceTheme`, `MACFlooding`, `Wigle`, `EthernetHelper`, `keyboard`, `String`?**
  _High betweenness centrality (0.165) - this node is a cross-community bridge._
- **Why does `loopOptions()` connect `loopOptions` to `Chameleon`, `TV-B-Gone.cpp`, `SRIXTool`, `shark_loop`, `TagOMatic`, `fm.cpp`, `box_t`, `rf_bruteforce.cpp`, `EspConnection`, `Pn532ble`, `karma_attack.cpp`, `nrf_mousejack.cpp`, `wifiConnectMenu`, `initRfModule`, `RFScan`, `ClockMenu`, `IrRead`, `wifi_repeater.cpp`, `ducky_typer.cpp`, `spam.cpp`, `main_menu.h`, `EMVReader`, `EthernetMenu`, `OthersMenu`, `SnifferPacket`, `display.cpp`, `PN532KillerTools.cpp`, `Opt_Coord`, `displayWarning`, `GpsMenu`, `optionsMenu`, `rf_send.cpp`, `brucegotchi_start`, `menu_js.cpp`, `rf_raw_record_create`, `RFID125`, `MainMenu`, `wifi_atks.cpp`, `drawMainBorderWithTitle`, `ARPScanner.cpp`, `LoRaMenu`, `obd_dashboard_setup`, `optionsMenu`, `displayTextLine`, `MassStorage`, `LoRaRF.cpp`, `wifiMACMenu`, `sniffer_setup`, `led_control.cpp`, `mykeyboard.cpp`, `loopSD`, `ibutton.cpp`, `RFMenu`, `dialog_js.cpp`, `ble_ninebot.cpp`, `evil_portal.cpp`, `displayError`, `selectPortalTemplate`, `webInterface.cpp`, `keyboard`, `ConfigMenu`?**
  _High betweenness centrality (0.133) - this node is a cross-community bridge._
- **Why does `getFsStorage()` connect `getFsStorage` to `ir_commands.cpp`, `Chameleon`, `BLE_Suite.cpp`, `SRIXTool`, `TagOMatic`, `karma_attack.cpp`, `box_t`, `EspConnection`, `Pn532ble`, `nrf_mousejack.cpp`, `readDecryptedFile`, `RFScan`, `padprintln`, `RFID2`, `_bytesToHex`, `wifi_crack_handshake`, `EMVReader`, `rf_keeloq.cpp`, `PN532.cpp`, `SnifferPacket`, `ST25R3916.cpp`, `GPSTracker`, `helpers.h`, `BackgroundPortal`, `RFID125`, `String`, `rf_commands.cpp`, `loadFile`, `loopSD`, `ibutton.cpp`, `mic.cpp`, `evil_portal.cpp`, `SSIDDatabase`, `displayError`, `selectPortalTemplate`, `saveHfDumpBinFile`, `sound_commands.cpp`, `vector`, `ConfigMenu`, `String`?**
  _High betweenness centrality (0.094) - this node is a cross-community bridge._
- **Are the 194 inferred relationships involving `loopOptions()` (e.g. with `beginSend` and `selectFile`) actually correct?**
  _`loopOptions()` has 194 INFERRED edges - model-reasoned connections that need verification._
- **Are the 172 inferred relationships involving `displayError()` (e.g. with `beginEspnow` and `beginSend`) actually correct?**
  _`displayError()` has 172 INFERRED edges - model-reasoned connections that need verification._
- **Are the 123 inferred relationships involving `padprintln()` (e.g. with `receiveFile` and `sendFile`) actually correct?**
  _`padprintln()` has 123 INFERRED edges - model-reasoned connections that need verification._
- **What connects `BruceConfig`, `tft_logger`, `netif` to the rest of the system?**
  _1133 weakly-connected nodes found - possible documentation gaps or missing edges._