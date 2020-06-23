##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Seventythree
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
LinkerName             :=/usr/bin/g++
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i 
IncludeSwitch          :=-I
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
OutputFileCmd          :=$(IntermediateDirectory)/$(ProjectName)Cmd
Preprocessors          :=$(PreprocessorSwitch)__WX__ $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Seventythree.txt"
ObjectsFileListCmd     :="SeventythreeCmd.txt"
MakeDirCommand         :=mkdir -p
LinkOptions            := `pkg-config --libs portaudiocpp` -s $(shell wx-config --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
CXX      := /usr/bin/g++
CXXFLAGS := -std=c++17 -O2 -Wall $(Preprocessors)
WXFLAGS  := $(shell wx-config --cxxflags --unicode=yes --debug=no)


##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/MainDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/ConfigFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/MorseDecode.cpp$(ObjectSuffix) $(IntermediateDirectory)/MorseStatistic.cpp$(ObjectSuffix) $(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MorseGUI.cpp$(ObjectSuffix) $(IntermediateDirectory)/Global.cpp$(ObjectSuffix) $(IntermediateDirectory)/Audio.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/MainCmdLine.cpp$(ObjectSuffix) $(IntermediateDirectory)/MorseDecode.cpp$(ObjectSuffix) $(IntermediateDirectory)/MorseStatistic.cpp$(ObjectSuffix)



##
## Main Build Targets 
##
.PHONY: all clean MakeIntermediateDirs
all: $(OutputFileCmd) $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects0) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(LinkOptions)

$(OutputFileCmd): $(IntermediateDirectory)/.d $(Objects1) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects1)  > $(ObjectsFileListCmd)
	$(LinkerName) $(OutputSwitch)$(OutputFileCmd) @$(ObjectsFileListCmd)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

##
## Objects
##
$(IntermediateDirectory)/MainDialog.cpp$(ObjectSuffix): MainDialog.cpp $(IntermediateDirectory)/MainDialog.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./MainDialog.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainDialog.cpp$(DependSuffix): MainDialog.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainDialog.cpp$(DependSuffix) -MM MainDialog.cpp

$(IntermediateDirectory)/MainDialog.cpp$(PreprocessSuffix): MainDialog.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainDialog.cpp$(PreprocessSuffix) MainDialog.cpp

$(IntermediateDirectory)/ConfigFile.cpp$(ObjectSuffix): ConfigFile.cpp $(IntermediateDirectory)/ConfigFile.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./ConfigFile.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ConfigFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConfigFile.cpp$(DependSuffix): ConfigFile.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ConfigFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ConfigFile.cpp$(DependSuffix) -MM ConfigFile.cpp

$(IntermediateDirectory)/ConfigFile.cpp$(PreprocessSuffix): ConfigFile.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConfigFile.cpp$(PreprocessSuffix) ConfigFile.cpp

$(IntermediateDirectory)/MorseDecode.cpp$(ObjectSuffix): MorseDecode.cpp $(IntermediateDirectory)/MorseDecode.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./MorseDecode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MorseDecode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MorseDecode.cpp$(DependSuffix): MorseDecode.cpp
	@$(CXX) $(CXXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MorseDecode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MorseDecode.cpp$(DependSuffix) -MM MorseDecode.cpp

$(IntermediateDirectory)/MorseDecode.cpp$(PreprocessSuffix): MorseDecode.cpp
	$(CXX) $(CXXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MorseDecode.cpp$(PreprocessSuffix) MorseDecode.cpp

$(IntermediateDirectory)/MorseStatistic.cpp$(ObjectSuffix): MorseStatistic.cpp $(IntermediateDirectory)/MorseStatistic.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./MorseStatistic.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MorseStatistic.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MorseStatistic.cpp$(DependSuffix): MorseStatistic.cpp
	@$(CXX) $(CXXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MorseStatistic.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MorseStatistic.cpp$(DependSuffix) -MM MorseStatistic.cpp

$(IntermediateDirectory)/MorseStatistic.cpp$(PreprocessSuffix): MorseStatistic.cpp
	$(CXX) $(CXXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MorseStatistic.cpp$(PreprocessSuffix) MorseStatistic.cpp

$(IntermediateDirectory)/Main.cpp$(ObjectSuffix): Main.cpp $(IntermediateDirectory)/Main.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./Main.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Main.cpp$(DependSuffix): Main.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Main.cpp$(DependSuffix) -MM Main.cpp

$(IntermediateDirectory)/Main.cpp$(PreprocessSuffix): Main.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Main.cpp$(PreprocessSuffix) Main.cpp

$(IntermediateDirectory)/MorseGUI.cpp$(ObjectSuffix): MorseGUI.cpp $(IntermediateDirectory)/MorseGUI.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./MorseGUI.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MorseGUI.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MorseGUI.cpp$(DependSuffix): MorseGUI.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MorseGUI.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MorseGUI.cpp$(DependSuffix) -MM MorseGUI.cpp

$(IntermediateDirectory)/MorseGUI.cpp$(PreprocessSuffix): MorseGUI.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MorseGUI.cpp$(PreprocessSuffix) MorseGUI.cpp

$(IntermediateDirectory)/Global.cpp$(ObjectSuffix): Global.cpp $(IntermediateDirectory)/Global.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./Global.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Global.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Global.cpp$(DependSuffix): Global.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Global.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Global.cpp$(DependSuffix) -MM Global.cpp

$(IntermediateDirectory)/Global.cpp$(PreprocessSuffix): Global.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Global.cpp$(PreprocessSuffix) Global.cpp

$(IntermediateDirectory)/Audio.cpp$(ObjectSuffix): Audio.cpp $(IntermediateDirectory)/Audio.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./Audio.cpp" $(CXXFLAGS) $(WXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Audio.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Audio.cpp$(DependSuffix): Audio.cpp
	@$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Audio.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Audio.cpp$(DependSuffix) -MM Audio.cpp

$(IntermediateDirectory)/Audio.cpp$(PreprocessSuffix): Audio.cpp
	$(CXX) $(CXXFLAGS) $(WXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Audio.cpp$(PreprocessSuffix) Audio.cpp

$(IntermediateDirectory)/MainCmdLine.cpp$(ObjectSuffix): MainCmdLine.cpp $(IntermediateDirectory)/MainCmdLine.cpp$(DependSuffix)
	$(CXX)  $(SourceSwitch) "./MainCmdLine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainCmdLine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainCmdLine.cpp$(DependSuffix): MainCmdLine.cpp
	@$(CXX) $(CXXFLAGS)  $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainCmdLine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainCmdLine.cpp$(DependSuffix) -MM MainCmdLine.cpp
$(IntermediateDirectory)/MainCmdLine.cpp$(PreprocessSuffix): MainCmdLine.cpp
	$(CXX) $(CXXFLAGS)  $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainCmdLine.cpp$(PreprocessSuffix) MainCmdLine.cpp

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


