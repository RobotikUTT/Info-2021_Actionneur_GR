from .can_description_parser import Device, Bind, Message, Field, Frame
from .can_description_parser import parse_devices, parse_messages, parse_frames

import os.path

_data_dir = os.path.join(os.path.dirname(__file__), '../can_description/')
_devices_filepath = os.path.join(_data_dir, 'devices.json')
_messages_filepath = os.path.join(_data_dir, 'messages.json')
_frames_filepath = os.path.join(_data_dir, 'frames.json')


devicesList = parse_devices(_devices_filepath)
"""A list of all `python_parser.can_description_parser.Device` described in the *devices.json* file."""

devicesById = {d.arbitration_id: d for d in devicesList}
"""A dictionary with the `python_parser.can_description_parser.Device` from `devicesList` accessible by their arbitration ID."""

devicesByName = {d.name: d for d in devicesList}
"""A dictionary with the `python_parser.can_description_parser.Device` from `devicesList` accessible by their name."""


messagesList = parse_messages(_messages_filepath)
"""A list of all `python_parser.can_description_parser.Message` described in the *messages.json* file."""


framesList = parse_frames(_frames_filepath)
"""A list of all `python_parser.can_description_parser.Frame` described in the *frames.json* file."""

framesByCmdId = {f.cmd_id: f for f in framesList}
"""A dictionary with the `python_parser.can_description_parser.Frame` from `framesList` accessible by their command ID."""

framesByName = {f.name: f for f in framesList}
"""A dictionary with the `python_parser.can_description_parser.Frame` from `framesList` accessible by their name."""
