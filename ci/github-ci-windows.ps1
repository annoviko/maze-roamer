$JobBuild = "test-maze-roamer-build"

$SolutionPath = (Get-Item .).FullName
$SolutionName = "maze-roamer.sln"

$ProjectUtPath = "$SolutionPath\tests\ut"
$ProjectUtName = "ut.vcxproj"

$BinaryUtPath = "$SolutionPath\x64\Release"
$BinaryUtName = "ut.exe"


function Announce-Step($Message) {
    Write-Host "[New Step] $Message" -ForegroundColor green
}


function Build-Application($Configuration) {
    Announce-Step "Build Application (configuration '$Configuration')."
    
    msbuild /p:RestorePackagesConfig=true /t:restore
    
    msbuild $SolutionName /t:maze-roamer /p:configuration=$Configuration /p:platform=x64
    if ($LastExitCode -ne 0) {
        Write-Error "[Error] Building crwproc failed with error code '$LastExitCode'."
        Exit 1
    }
}


function Build-UnitTests {
    Announce-Step "Build Unit-Tests."
    
    msbuild /p:RestorePackagesConfig=true /t:restore
    
    msbuild $SolutionName /t:ut /p:configuration=release /p:platform=x64
    if ($LastExitCode -ne 0) {
        Write-Error "[Error] Building unit-test project failed with error code '$LastExitCode'."
        Exit 1
    }
}


function Run-UnitTests {
    Announce-Step "Run Unit-Tests."
    
    Build-UnitTests
    
    cd $BinaryUtPath
    
    & "$BinaryUtPath\$BinaryUtName"
    
    if ($LastExitCode -ne 0) {
        Write-Error "[Error] Unit-testing failed with error code '$LastExitCode'."
        Exit 1
    }
    
    cd $SolutionPath
}


function Run-BuildTestJob {
    Announce-Step "Run Build Test Job."
    
    Build-Application "Release"
	Build-Application "Debug"
	
	Run-UnitTests
}


function Run-ContinousIntegration($Job) {
    switch($Job) {
        $JobBuild { 
            Run-BuildTestJob
            break
        }
        default {
            Write-Error "Unknown job is specified '$Job'." -TargetObject $Job
            Exit 1
        }
    }
}


Run-ContinousIntegration $args[0]
