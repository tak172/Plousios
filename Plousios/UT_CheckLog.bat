@echo off
cd
echo Текущая директория: %CD%
set xml_file=%1
for /f "tokens=3 delims=<>" %%a in ('findstr /C:"<FailuresTotal>" "%xml_file%"') do set failures_total=%%a
if %failures_total% gtr 0 (
  echo CppUnit tests have failures! See XML for details.
  exit /b 1
)
echo CppUnit tests passed successfully!