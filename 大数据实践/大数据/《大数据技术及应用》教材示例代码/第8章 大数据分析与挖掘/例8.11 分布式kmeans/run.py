import os
cmd = "mapred streaming \
 -input /km_in \
 -output /km_out \
 -mapper /codes/mrkm_mapper.py \
 -reducer /codes/mrkm_reducer.py \
 -combiner /codes/mrkm_combiner.py"
os.system(cmd)