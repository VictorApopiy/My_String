pipeline {
	agent any
	stages {
		stage('SCM') {
			steps { 
				checkout scm
			}
		}
		
		stage("Build") {
			steps {
				dir("Exercise/build") {
					sh 'cmake ../ -DCMAKE_BUILD_TYPE=Debug'
					sh 'make tests'
				}
			}
		}
		stage("Test") {
			steps {
				dir("Exercise/build") {
					sh 'ctest'
				}
			}
		}
		stage("Check coverage"){
			steps{
				dir("Exercise/build") {
					sh 'make tests_coverage'
					cobertura autoUpdateHealth: false, autoUpdateStability: false, coberturaReportFile: 'test_coverage.xml', conditionalCoverageTargets: '70, 0, 0', failUnhealthy: false, failUnstable: false, lineCoverageTargets: '80, 0, 0', maxNumberOfBuilds: 0, methodCoverageTargets: '80, 0, 0', onlyStable: false, sourceEncoding: 'ASCII', zoomCoverageChart: false
				}
			}

		}
		stage("Build main"){
			steps {
				dir("Exercise/build") {
					sh 'make main'
				}
				dir('Exercise/build/cobertura_reports/'){
					mv ../test_coverage.xml ./
				}
				publishCoverage adapters: [cobertura(path: 'Exercise/build/cobertura_reports/', thresholds: [[failUnhealthy: true, thresholdTarget: 'Aggregated Report', unhealthyThreshold: 80.0, unstableThreshold: 80.0]])], sourceFileResolver: sourceFiles('NEVER_STORE')
				script {
					currentBuild.result = 'SUCCESS'
				}
			}
		}
	}
}
