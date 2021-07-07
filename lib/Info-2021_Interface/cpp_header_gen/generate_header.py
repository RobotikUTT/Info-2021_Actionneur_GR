#!/usr/bin/python3

import sys
import os
sys.path.insert(1, os.path.join(sys.path[0], '..'))		# Needed to import from parent directory
from python_parser import framesList


output_file = os.path.join(os.path.dirname(__file__), 'protocol.gen.hpp')

content = [
	'// PROTOCOL (frame_id, param_length, [params sizes]) --> generated with Python'
]
contents = []

for frame in framesList:

	data = '{{{}, {}}}'.format(
		frame.cmd_id,
		', '.join(
			[str(len(frame.fields))] + ['1' if field._type == 'byte' else '2' for field in frame.fields] + ['0' for i in range(8 - len(frame.fields))]
		)
	)
	contents.append(data)

	content.append('const uint8_t {}[] = {};'
		.format(frame.name.upper(), data))

content.append('const uint8_t FRAMES[][10] = {{\n\t{}\n}};'.format(',\n\t'.join(contents)))
content.append('const int FRAMES_LENGTH = {};'.format(len(contents)))
content.append('// END OF PROTOCOL')

with open(output_file, 'w') as file:
	file.write('\n'.join(content))
	file.write('\n')
