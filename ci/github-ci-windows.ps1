$JobBuild = "test-maze-roamer-build"

$SolutionPath = (Get-Item .).FullName
$SolutionName = "maze-roamer.sln"


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


function Run-BuildTestJob {
    Announce-Step "Run Build Test Job."
    
    Build-Application "Release"
	Build-Application "Debug"
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
