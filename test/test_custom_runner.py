# refer to this GitHub issue
# https://github.com/platformio/platformio-core/issues/4276#issuecomment-1145840723

import click

from platformio.public import UnityTestRunner

class CustomTestRunner(UnityTestRunner):

    def on_testing_line_output(self, line):
        click.echo(line, nl=False)
        super().on_testing_line_output(line)