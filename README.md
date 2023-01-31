# demo-io-plink

## Cấu trúc gói tin
### Gói tin command từ web gửi đến device:
- Topic: v1/demo/web/cmd
- Message: string
`on/off`

### Gói tin ACK từ device gửi đến web:
- Topic: v1/demo/device/ACK
- Message: json
```javascript
{
  "cmd": "on" || "off",
  "input_relay": true,
  "input_emergency": true,
}
```

### API lấy last status:
`GET https://nodered.plink-things.com/v1/demo/last-status`
Response message: json
```json
{
  "lastStatus": {
    "relay_IO": {
      "in_0": true,
      "out_0": true
    },
    "emergency": {
      "in_1": true,
      "out_1": true
    },
    "timestamp": 1675132651012
  }
}
```
