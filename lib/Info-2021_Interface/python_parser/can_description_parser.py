from dataclasses import dataclass, field
from typing import List, Dict

import json


@dataclass
class Device:
	name: str
	arbitration_id: int


@dataclass
class Bind:
	frame: str
	message: str


@dataclass
class Message:
	direction: str
	binds: List[Bind]


@dataclass
class Field:
	name: str
	_type: str
	enum: Dict[str, int] = field(default_factory=dict)
	r_enum: Dict[int, str] = field(default_factory=dict)


@dataclass
class Frame:
	name: str
	description: str
	cmd_id: int
	source: str
	destination: str
	fields: list


def parse_devices(devices_filepath):
	"""
	Return a list of `python_parser.can_description_parser.Device` objects.
	"""
	with open(devices_filepath, 'r') as f:
		devices = json.load(f)["devices"]

	return [Device(**device) for device in devices]


def parse_messages(messages_filepath):
	"""
	Return a list of `python_parser.can_description_parser.Message` objects.
	"""
	with open(messages_filepath, 'r') as f:
		messages = json.load(f)["messages"]

	return [Message(message["direction"], [Bind(**bind) for bind in message["binds"]]) for message in messages]


def parse_frames(frames_filepath):
	"""
	Return a list of `python_parser.can_description_parser.Frame` objects.
	"""
	with open(frames_filepath, 'r') as f:
		frames = json.load(f)["frames"]

	framesList = []
	for frame in frames:
		frame['fields'] = [Field(**field, r_enum=dict(((v, k) for k, v in field.get('enum', {}).items()))) for field in frame['fields']]
		framesList.append(Frame(**frame))
	return framesList
