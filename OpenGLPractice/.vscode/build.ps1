param(
    [string]$Configuration = 'Debug',
    [string]$Platform = 'x86'
)

$vswhere = 'C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe'
$msbuild = @(& $vswhere -latest -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe')[0]
$sln = Join-Path $PSScriptRoot '..\OpenGLPractice.sln'

& $msbuild $sln /p:Configuration=$Configuration /p:Platform=$Platform /m
exit $LASTEXITCODE
