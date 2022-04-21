$error_ = 0

$error_++
MSBuild /property:Configuration=Release /property:Platform=x86 -t:Clean || Exit $error_

$error_++
MSBuild /property:Configuration=Release /property:Platform=x86 -t:Build || Exit $error_

$error_++
Test-Path ".\Release\netflixq.exe" -PathType Leaf || Exit $error_

$error_++
Move-Item -Path ".\Release\netflixq.exe" -Destination ".\Release\netflixq-x86.exe" -Force || Exit $error_

$error_++
MSBuild /property:Configuration=Release /property:Platform=x64 -t:Clean || Exit $error_

$error_++
MSBuild /property:Configuration=Release /property:Platform=x64 -t:Build || Exit $error_


$error_++
Test-Path ".\x64\Release\netflixq.exe" -PathType Leaf || Exit $error_

$error_++
Move-Item -Path ".\x64\Release\netflixq.exe" -Destination ".\x64\Release\netflixq-x64.exe" -Force || Exit $error_