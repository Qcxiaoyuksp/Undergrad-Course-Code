<template>
  <div class="weather">
<!--    <h1>Results</h1>-->
    <ul>
      <li v-for="item in results" :key="item.id">{{ item.name }}</li>
    </ul>
    <div class="wearther_img">

    <div v-if="response" class="weather">
      <img :src="src"/>
      <span class="label">{{ response.date }}</span><br>
      <span  class="label">{{ week }}</span>
      <span  class="label">{{ response.dayweather }}</span>
      <span  class="label"> {{ response.daytemp }}℃</span>
    </div>
      <div v-else>
        ......
      </div>
    </div>
  </div>

</template>

<script lang="ts" setup>
import * as API from '../api';
import { ref, computed } from 'vue';
import type { Ref } from 'vue';
          // const  dayDate=ref({});
          // const  dayWeather=ref({});
          // const  dayWeek=ref({});
          // const  dayTemp=ref({})
          // const  nightWeather=ref({})


type A = { week: number, dayweather: string }

const response: Ref<A | null> = ref(null)

const week = computed(() => {
  const weekIndex = response.value!.week;
  if(weekIndex >= 1 && weekIndex <=7){
    const weeks = ['一','二','三','四','五','六','日']
    return '周'+ weeks[weekIndex - 1]
  }else {
    return '';
  }

  // return '周'+ weeks[response.value.week - 1]
});


const src = computed(() => {
  const imgs = {
    '晴': '/src/assets/images/qing.png',
    '多云': '/src/assets/images/duoyun.png',
    '小雨':'/src/assets/images/xiaoyu.png',
    '晚晴':'/src/assets/images/yeqing.png',
    '晚多云':'/src/assets/images/yeduoyun.png'
  };
  return imgs[response.value!.dayweather || ''];
})

function init(){
  API.getWeatherInfo(null).then((res)=>{
    if(res.success){
      response.value = res.result
    }
  });
}

setInterval(init, 10000)
</script>
<style scoped>
.weather{
  color: #ffffff;
  font-size: 16px;
  position: relative;
  top: 60px;
  left: 100px;
}
.flex-container {
  display: flex;
  flex-direction: column;
  align-items: flex-start;
}

img {
  margin-bottom: 10px;
}
.imgs{
  margin-bottom: 150px;
}
.label{
  margin-left: 50px;
}
</style>
