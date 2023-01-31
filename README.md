# demo-io-plink

## Cấu trúc gói tin
### Gói tin command từ web gửi đến device:
- Topic: `v1/demo/web/cmd`
- Message: json
```json
{
  "output": true
}
```

### Gói tin ACK từ device gửi đến web:
- Topic: `v1/demo/device/ACK`
- Message: json
```javascript
{
  "output": true,
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
    "output": true,
    "input_relay": true,
    "input_emergency": true,
    "timestamp": 1675151258340
  }
}
```
