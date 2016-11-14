setwd("/home/dosimont/Git/programs/ptools/lpaggreg/R")

lpaggreg_location="/opt/ptools/lpaggreg";
source("lpaggreg.R", echo=TRUE, local=TRUE)
source("lpaggreg_pjdump.R", echo=TRUE, local=TRUE)

#Threshold: 0<th<1, lower value means more accuracy for retrieving the list of partitions but longer computation time
th=0.001

trace=parsepjdump("nemo.exe.128tasks.chop1.clustered.counters-only.pjdump")

trace$data<-trace$data[(trace$data$Type %in% c('(PAPI_TOT_INS) Instr completed', '(PAPI_TOT_CYC) Total cycles')),]

micro=pjdump2micro(trace,100, "Counter")
print(micro)

hdf<-haggregate(micro$data, micro$hierarchy, th)

qualplot(hdf)
hplot_treemap_perfcounter(hmacro(hdf$Partitions, micro, hdf$POpt))
hplot_treemap_perfcounter(hmacro(hdf$Partitions, micro, hdf$Qualities[5,"Parameter"]))

trace$data<-trace$data[(trace$data$Type %in% c('(PAPI_TOT_INS) Instr completed')),]

micro=pjdump2micro(trace,100, "Counter")
hdf<-haggregate(micro$data, micro$hierarchy, th)

qualplot(hdf)
hplot_treemap_perfcounter(hmacro(hdf$Partitions, micro, hdf$POpt))