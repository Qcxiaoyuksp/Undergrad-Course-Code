<template>
<!--  <IndexDef v-if="indexStyle === 0"></IndexDef>-->
  <!-- <IndexChart v-if="indexStyle === 1"></IndexChart>
   <IndexBdc v-if="indexStyle == 2"></IndexBdc>
   <IndexTask v-if="indexStyle == 3"></IndexTask>
   <div style="width: 100%; text-align: right; margin-top: 20px">
     请选择首页样式：
     <a-radio-group v-model:value="indexStyle">
       <a-radio :value="0">默认</a-radio>
       <a-radio :value="1">销量统计</a-radio>
       <a-radio :value="2">业务统计</a-radio>
       <a-radio :value="3">我的任务</a-radio>
     </a-radio-group>
   </div>-->
<!--  <div><a href="https://restapi.amap.com/v3/weather/weatherInfo?key=d28c2cbc9f57836f815e707eb07ee9b0&city=220100&extensions=all">点击查看天气</a></div>-->
  <div class="home" >
    <IndexWeather></IndexWeather>
    <nav>
      <ul>
        <li> <a><img  class="img1" src="../../../assets/images/u21.png"></a></li>
        <li> <a><img class="img2" src="../../../assets/images/u22.png"></a></li>
        <li>  <a><img class="img3" src="../../../assets/images/u23.png"></a></li>
      </ul>
    </nav>
    <nav>
      <div class="meTicket">
        <span><a><img class="img4" src="../../../assets/images/u20.png"></a></span>
        <span><a><img class="img5" src="../../../assets/images/u25.png"></a></span>
      </div>
    </nav>

  </div>
  <div class="meTicket">
    <span> </span>
    <span></span>
  </div>
  <div id="app">
    <div>{{ responseText }}</div>
  </div>
</template>

<script lang="ts" setup>
  import { ref } from 'vue';
   // import IndexDef from './homePage/IndexDef.vue';
  import IndexWeather from './homePage/weather.vue';
  // import Index from "@/views/demo/comp/desc/index.vue";
  // export default {
  //   components: {Index}
  // }
  //  import IndexChart from './homePage/IndexChart.vue';
 //  import IndexBdc from './homePage/IndexBdc.vue';
 //  import IndexTask from './homePage/IndexTask.vue';
 //
 //  const indexStyle = ref(0);
</script>

<style>
.home{
  background-image: url("../../../assets/images/u26.png");
  background-size: cover;
  width: 100%;
  height: 100%;
}
nav{
  padding: 200px 100px 150px 100px;
}
nav ul{
  display: flex;
  justify-content: space-between;
  align-items: flex-end;
}
nav .meTicket
.img4,
.img5{
  margin-bottom: 0px;
  margin-right: 140px;
  margin-left: 300px;
  margin-top: -450px;
}

</style>
