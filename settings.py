from datetime import datetime
from pathlib import Path


def get_active_branch_name():
    head_dir = Path(".") / ".git" / "HEAD"
    with head_dir.open("r") as f:
        content = f.read().splitlines()

    for line in content:
        if line[0:4] == "ref:":
            return line.partition("refs/heads/")[2]


Import("env")

settings = {
    "SG1": {
        "RADIO_FREQUENCY": 915 - 0.5 * 2,
        "RADIO_BANDWIDTH": 250,
        "RADIO_SPREADING_FACTOR": 5,
        "RADIO_CODING_RATE": 8,
        "RADIO_SYNC_WORD": 0x22,
    },
    "SG2": {
        "RADIO_FREQUENCY": 915 - 0.5,
        "RADIO_BANDWIDTH": 250,
        "RADIO_SPREADING_FACTOR": 5,
        "RADIO_CODING_RATE": 8,
        "RADIO_SYNC_WORD": 0x32,
    },
    "SG3": {
        "RADIO_FREQUENCY": 915.00,
        "RADIO_BANDWIDTH": 250,
        "RADIO_SPREADING_FACTOR": 5,
        "RADIO_CODING_RATE": 8,
        "RADIO_SYNC_WORD": 0x42,
    }
}

print(f"Enter the stage of the rocket ({', '.join(settings.keys())}):")
stage = input().upper().strip()

if stage not in settings.keys():
    raise ValueError("Invalid stage name")
    exit(1)

env.Append(CPPDEFINES=["STAGE_CONFIG"])

for key, value in settings[stage].items():
    print("Adding define: " + key + " = " + str(value))
    env.Append(CPPDEFINES=[(key, value)])

env.Append(CPPDEFINES=[
    ("STAGE_NAME", env.StringifyMacro(stage))
])

ground_stations = ["GS1", "GS2", "GS3"]

# if we are the ground station then we set the ground station identifier
if env.get('PIOENV') == 'ground':
    print(f"Which ground station is this? ({', '.join(ground_stations)}):")
    ground_station = input().upper().strip()
    if ground_station not in ground_stations:
        raise ValueError("Invalid GS name")
        exit(1)

    env.Append(CPPDEFINES=[
        ("GS_NAME", env.StringifyMacro(ground_station))
    ])
