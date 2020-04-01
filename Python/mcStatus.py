import requests
import json
api = "https://api.cdcp.pw:4443/ping/serverping.php?ip=106.15.72.2&port=23333"
while True:
    raw = requests.get(api)
    info = raw.json()
    print("status:",info["status"])
    print("version:",info["version"])
    print("player:%d/%d" % (info["online"],info["max"]))
    input("[Enter] to refresh...")