<template>
	<Demo @hello="showHelloMsg" msg="你好啊" school="Vue知识">
		<template v-slot:qwe>
			<span>Vue知识</span>
		</template>
		<template v-slot:asd>
			<span>Vue知识</span>
		</template>
	</Demo>
</template>

<script>
	import Demo from './components/Demo'
	export default {
		name: 'App',
		components:{Demo},
		setup(){
			function showHelloMsg(value){
				alert(`你好啊，你触发了hello事件，我收到的参数是:${value}！`)
			}
			return {
				showHelloMsg
			}
		}
	}
</script>

